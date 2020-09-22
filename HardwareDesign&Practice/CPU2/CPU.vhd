----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    09:52:55 06/29/2019 
-- Design Name: 
-- Module Name:    CPU - Behavioral 
-- Project Name: 
-- Target Devices: 
-- Tool versions: 
-- Description: 
--
-- Dependencies: 
--
-- Revision: 
-- Revision 0.01 - File Created
-- Additional Comments: 
--
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use ieee.std_logic_unsigned.all;
use IEEE.STD_LOGIC_ARITH.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;





entity CPU is
    Port (  CLK : in  STD_LOGIC;
            RST : in  STD_LOGIC;
			   clk0 : in STD_LOGIC;
			   showCtrl : in STD_LOGIC;
            bZero_ctrl : in STD_LOGIC;
            ADDR : out  STD_LOGIC_VECTOR (15 downto 0);  --RAM地址
            DATA : inout  STD_LOGIC_VECTOR (15 downto 0);  --RAM数据
            INPUT : in  STD_LOGIC_VECTOR (15 downto 0);  --拨码开关输入
            OUTPUT : out  STD_LOGIC_VECTOR (15 downto 0);  --LED
            CONTROL : in  STD_LOGIC;--RW状态转换
            clk_rw : in STD_LOGIC; --控制读写进程
            RAM1_EN : out  STD_LOGIC;  --RAM使能
            RAM1_OE : out  STD_LOGIC;  --RAM读使能
            RAM1_WE : out  STD_LOGIC;  --RAM写使能
            stateCnt_L : out  STD_LOGIC_VECTOR (6 downto 0);--左数码管,显示四种状态
            stateCnt_R : out  STD_LOGIC_VECTOR (6 downto 0);--右数码管，显示当前周期
            dbc : out  STD_LOGIC
    );
end CPU;

--从内存中分配8个地址空间给8个寄存器，地址从0000H到0010H
--从内存中分配地址空间给ADDU指令，0010H ~ 001FH
--从内存中分配地址空间给SUBU指令，0020H ~ 002FH
--从内存中分配地址空间给BEQZ指令，0030H ~ 003FH
--从内存中分配地址空间给JR指令，0040H ~ 004FH
--从内存中分配地址空间给XOR指令，0050H ~ 005FH
--从内存中分配地址空间给LW指令，0060H ~ 006FH
--从内存中分配地址空间给SW指令，0070H ~ 007FH
--实际实现：从内存顺序存取指令，不分空间

architecture Behavioral of CPU is

type state is (instruction_fetch,decode,execute,mem_control,write_reg);
signal CU_state: state;
type show is (PC,ALU,M,REG);
signal State_show: show;
signal instruction : std_logic_vector(15 downto 0);
signal RegDst : std_logic_vector(1 downto 0);
signal RegWrite : std_logic_vector(2 downto 0);
signal MemtoReg : std_logic_vector(1 downto 0);
signal ALUSrcA : std_logic;
signal ALUSrcB : std_logic_vector(1 downto 0);
signal ALUOp : std_logic_vector(1 downto 0);
signal MemRead : std_logic;
signal MemWrite : std_logic;
signal IorD : std_logic;
signal IRWrite : std_logic;
signal PcWrite : std_logic;
signal PCSource : std_logic;
signal PcWriteCond : std_logic;

signal tmp_addr:STD_LOGIC_VECTOR (15 downto 0):=x"0000";
signal tmp_read_addr:STD_LOGIC_VECTOR (15 downto 0):=x"0000";
signal tmp_data:STD_LOGIC_VECTOR (15 downto 0):=x"0000";
signal tmp_addr1:STD_LOGIC_VECTOR (15 downto 0):=x"0000";
signal tmp_read_addr1:STD_LOGIC_VECTOR (15 downto 0):=x"0000";
signal tmp_data1:STD_LOGIC_VECTOR (15 downto 0):=x"0000";
signal tmp_light : std_logic_vector(15 downto 0);
type prj_state is(N,R,W);
signal ctrl_state : prj_state;
type sram_state is(waiting,prepare,start,over);
signal write_state,read_state : sram_state;
signal control_state : integer range 0 to 5;
signal instruction_fetch_state : integer range 0 to 3; 

signal bZero : std_logic;  
signal rx,ry,rz : STD_LOGIC_VECTOR (2 downto 0);
signal im : STD_LOGIC_VECTOR (4 downto 0);
signal IMD : STD_LOGIC_VECTOR (7 downto 0);

begin

process(RST,showCtrl)
    begin
        if RST = '0' then
           State_show <= PC;
           stateCnt_L <= "0111001";
        elsif showCtrl'event and showCtrl = '1' then
            case State_show is
                when PC =>
                    stateCnt_L <= "0000110";
                    State_show <= ALU;
                when ALU =>
                    stateCnt_L <= "1011011";
                    State_show <= M;
                when M =>
                    stateCnt_L <= "1001111";
                    State_show <= REG;
                when REG =>
                    stateCnt_L <= "1100110";
                    State_show <= PC;
             end case;
         end if;
     end process;
                
process(RST,bZero_ctrl)
    begin
        if RST = '0' then
           bZero <= '0';
        elsif bZero_ctrl'event and bZero_ctrl = '1' then 
           if bZero = '0' then
			     bZero <= '1';
			  elsif bZero = '1' then
			     bZero <= '0';
			  end if;
        end if;
    end process;
	 
process(bZero)
   begin
	     if bZero = '0' then
		     PcWriteCond <= '0';
		  elsif bZero ='1' then
		     PcWriteCond <= '1';
		  end if;
	end process;

process(RST, CLK,CONTROL)
	begin
		if RST = '0' then 
            CU_state <= instruction_fetch; 
            stateCnt_R <= "0011110";
			   instruction <= "0000000000000000";
			   RegDst <= "00";
			   RegWrite <= "000";
			   MemtoReg <= "00";
			   ALUSrcA <= '0';
			   ALUSrcB <= "00";
			   ALUOp <= "00";
			   MemRead <= '0';
			   MemWrite <= '0';
			   IorD <= '0';
			   IRWrite <= '0';
			   PcWrite <= '0';
			   PCSource <= '0';
				
				instruction_fetch_state <= 0;
				
				tmp_data <=x"0000";
            tmp_read_addr <="0000000000000000";
            tmp_addr <="0000000000000000";
				control_state <= 0;
            RAM1_EN <= '1';        --RAM1的片选信号
            RAM1_OE <= '0';        --读信号
            RAM1_WE <= '0';        --写信号
		elsif CLK'event and CLK = '1' then
			case CU_state is
			
                when instruction_fetch =>
					     --case instruction_fetch_state is
						      --when 0 =>
						          --RAM1_EN <= '0';
								    --RAM1_OE <= '1';
								    --RAM1_WE <= '1';
								    --tmp_read_addr <= INPUT;
								    --instruction_fetch_state <= 1;
								--when 1 =>
								    --ADDR <= INPUT;
									 --DATA <= (others=> 'Z');
									 --RAM1_OE <= '0';
								    --RAM1_WE <= '1';
									 --instruction_fetch_state <= 2;
							   --when 2 =>
									 instruction <= INPUT;
									 stateCnt_R <= "0000110";
								    RegDst <= "00";
									 RegWrite <= "000";
									 MemtoReg <= "00";
									 ALUSrcA <= '0';
									 ALUSrcB <= "01";
									 ALUOp <= "00";
									 MemRead <= '1';
									 MemWrite <= '0';
									 IorD <= '0';
									 IRWrite <= '1';
									 PcWrite <= '1';
									 PCSource <= '0';
									 instruction_fetch_state <= 0;
									 CU_state <= decode;
                        --when others =>
                            --null;
                    --end case;									 
                
                when decode => 
                    stateCnt_R <= "1011011";
                    AluSrcA <= '0';
                    ALUSrcB <= "10";
                    ALUOp <= "00";
                    MemRead <= '0';
                    IRWrite <= '0';
                    PcWrite <= '0';
                    CU_state <= execute;
                    case instruction(15 downto 11) is
                        when "11100" =>
                            rx <= instruction(10 downto 8);
                            ry <= instruction(7 downto 5);
                            rz <= instruction(4 downto 2);
                        when "00100" =>   --BEQZ
                            rx <= instruction(10 downto 8);
                            IMD <= instruction(7 downto 0);
                        when "11101" =>
                            case instruction(4 downto 0) is
                                when "00000" =>    --JR
                                    rx <= instruction(10 downto 8);
                                when "01110" =>    --XOR
                                    rx <= instruction(10 downto 8);
                                    ry <= instruction(7 downto 5);
										  when others =>
										      null;
                            end case;
                        when "10011" =>    --LW
                            rx <= instruction(10 downto 8);
                            ry <= instruction(7 downto 5);
                            im <= instruction(4 downto 0); 
                        when "11011" =>    --SW
                            rx <= instruction(10 downto 8);
                            ry <= instruction(7 downto 5);
                            im <= instruction(4 downto 0);
								when others =>
								    null;
                    end case;
                
                when execute =>
                    stateCnt_R <= "1001111";
						  control_state <= 0;
                    case instruction(15 downto 11) is
                        when "11100" =>
                            if instruction(1 downto 0) = "01" then    --ADDU
                                ALUSrcA <= '1';
                                ALUSrcB <= "00";
                                ALUOp <= "00";
                            elsif instruction(1 downto 0) = "11" then  --SUBU
                                ALUSrcA <= '1';
                                ALUSrcB <= "00";
                                ALUOp <= "01";
                            end if;
                            CU_state <= write_reg;
                        when "00100" =>   --BEQZ
                            ALUSrcA <= '1';
                            ALUOp <= "10";
                            PCSource <= '1';
                            CU_state <= instruction_fetch;
                        when "11101" =>
                            case instruction(4 downto 0) is
                                when "00000" =>    --JR
                                    ALUSrcA <= '1';
                                    ALUOp <= "10";
                                    PcWrite <= '1';
                                    PCSource <= '0';
                                    CU_state <= instruction_fetch;
                                when "01110" =>    --XOR
                                    ALUSrcA <= '1';
                                    ALUSrcB <= "00";
                                    ALUOp <= "10";
                                    CU_state <= write_reg;
										  when others =>
										      null;
                            end case;
                        when "10011" =>    --LW
                            ALUSrcA <= '1';
                            ALUSrcB <= "10";
                            ALUOp <= "00";
                            CU_state <= write_reg;  
                        when "11011" =>    --SW
                            ALUSrcA <= '1';
                            ALUSrcB <= "10";
                            ALUOp <= "00";
                            CU_state <= write_reg;
								when others =>
									 null;
                    end case;
                
                when mem_control => 
                    stateCnt_R <= "1100110";
                     case instruction(15 downto 11) is
                        when "10011" =>    --LW
                            RegWrite <= "000";
                            MemRead <= '1';
                            IorD <= '1';
                            PcWrite <= '0';
									 case control_state is
									     when 2 =>
												RAM1_EN <= '0';
												RAM1_OE <= '1';
												RAM1_WE <= '1';
												DATA(4 downto 0) <= DATA(4 downto 0) + im;
												tmp_read_addr <= DATA;
												CU_state <= mem_control;
												control_state <= 3;
										  when 3 =>
												ADDR <= tmp_read_addr;
												DATA <= (others=>'Z');
												RAM1_OE<='0';
												RAM1_WE<='1';
												CU_state <= write_reg;
												control_state <= 4;
										  when others =>
										      null;
									 end case;
                        when "11011" =>    --SW
                            RegWrite <= "000";
                            MemWrite <= '1';
                            IorD <= '1';
                            PcWrite <= '0';
									 case control_state is
									     when 4 =>
												RAM1_EN <= '0';
												RAM1_OE <= '1';
												RAM1_WE <= '1';
												DATA(4 downto 0) <= DATA(4 downto 0) + im;
												tmp_addr <= DATA;
												CU_state <= mem_control;
												control_state <= 5;
										  when 5 =>
												ADDR <= tmp_addr;
												DATA <= tmp_data;
												RAM1_WE<='0';
												RAM1_OE<='1';
												CU_state <= write_reg;
												control_state <= 0;
										  when others =>
										      null;
									 end case;
								when others =>
									 null;
							end case;
						  
				     
               
                when write_reg =>
                    stateCnt_R <= "1101101";
                     case instruction(15 downto 11) is
                        when "11100" =>
                            case instruction(1 downto 0) is
                                when "01" =>    --ADDU
                                    RegDst <= "01";
                                    RegWrite <= "001";
                                    MemtoReg <= "00";
                                    MemRead <= '0';
                                    MemWrite <= '0';
												case  control_state is
													 when 0 =>
														   RAM1_EN <= '0';
															RAM1_OE <= '1';
															RAM1_WE <= '1';
														   tmp_addr1 <= "0000000000000000";
															tmp_read_addr1 <="0000000000000000";
															tmp_read_addr1(2 downto 0) <= rx;
															CU_state <= write_reg;
															control_state <= 1;
													 when 1 =>
															ADDR <= tmp_read_addr1;
															DATA <= (others=>'Z');
															RAM1_OE<='0';
															RAM1_WE<='1';
															CU_state <= write_reg;
															control_state <= 2;
													 when 2 => 
															RAM1_EN <= '0';
															RAM1_OE <= '1';
															RAM1_WE <= '1';
															tmp_data1 <= DATA;
															tmp_read_addr1 <="0000000000000000";
															tmp_read_addr1(2 downto 0) <= ry;
															CU_state <= write_reg;
															control_state <= 3;
													 when 3 => 
															ADDR <= tmp_read_addr1;
															DATA <= (others=>'Z');
															RAM1_OE<='0';
															RAM1_WE<='1';
															CU_state <= write_reg;
															control_state <= 4;
													 when 4 =>
															RAM1_EN <= '0';
															RAM1_OE <= '1';
															RAM1_WE <= '1';
															tmp_data1 <= DATA + tmp_data1;
															tmp_addr1(2 downto 0) <= rz;
															CU_state <= write_reg;
															control_state <= 5;
													 when 5 =>
															ADDR <= tmp_addr1;
															DATA <= tmp_data1;
															RAM1_WE<='0';
															RAM1_OE<='1';
															CU_state <= instruction_fetch;
															control_state <= 0;
													 when others =>
															null;
											   end case;
                                when "11" =>   --SUBU
                                    RegDst <= "01";
                                    RegWrite <= "001";
                                    MemtoReg <= "00";
                                    MemRead <= '0';
                                    MemWrite <= '0';
												case control_state is
													 when 0 =>								
														  RAM1_EN <= '0';
														  RAM1_OE <= '1';
														  RAM1_WE <= '1';
														  tmp_addr <= "0000000000000000";
														  tmp_read_addr <="0000000000000000";
														  tmp_read_addr(2 downto 0) <= rx;
														  CU_state <= write_reg;
														  control_state <= 1;
													 when 1 =>
														  ADDR <= tmp_read_addr;
														  DATA <= (others=>'Z');
														  RAM1_OE<='0';
														  RAM1_WE<='1';
														  CU_state <= write_reg;
														  control_state <= 2;
													 when 2 =>
														  RAM1_EN <= '0';
														  RAM1_OE <= '1';
														  RAM1_WE <= '1';
														  tmp_data <= DATA;
														  tmp_read_addr <="0000000000000000";
														  tmp_read_addr(2 downto 0) <= ry;
														  CU_state <= write_reg;
														  control_state <= 3;
													 when 3 =>
														  ADDR <= tmp_read_addr;
														  DATA <= (others=>'Z');
														  RAM1_OE<='0';
														  RAM1_WE<='1';
														  CU_state <= write_reg;
														  control_state <= 4;
													 when 4 =>
														  RAM1_EN <= '0';
														  RAM1_OE <= '1';
														  RAM1_WE <= '1';
														  tmp_data <= tmp_data - DATA;
														  tmp_addr(2 downto 0) <= rz;
														  CU_state <= write_reg;
														  control_state <= 5;
													 when 5 =>
														  ADDR <= tmp_addr;
														  DATA <= tmp_data;
														  RAM1_WE<='0';
														  RAM1_OE<='1';
														  CU_state <= instruction_fetch;
														  control_state <= 0;
													 when others =>
														  null;
												end case;
										  when others =>
										      null;
                             end case;
                        
                        when "11101" =>   --XOR
                            RegDst <= "00";
                            RegWrite <= "001";
                            MemtoReg <= "00";
                            MemRead <= '0';
                            MemWrite <= '0';
									 case control_state is
										  when 0 =>
												RAM1_EN <= '0';
												RAM1_OE <= '1';
												RAM1_WE <= '1';
												tmp_addr <= "0000000000000000";
												tmp_read_addr <="0000000000000000";
												tmp_read_addr(2 downto 0) <= rx;
												CU_state <= write_reg;
												control_state <= 1;
										  when 1 =>
												ADDR <= tmp_read_addr;
												DATA <= (others=>'Z');
												RAM1_OE<='0';
												RAM1_WE<='1';
												CU_state <= write_reg;
												control_state <= 2;
										  when 2 => 
												RAM1_EN <= '0';
												RAM1_OE <= '1';
												RAM1_WE <= '1';
												tmp_data <= DATA;
												tmp_read_addr <="0000000000000000";
												tmp_read_addr(2 downto 0) <= ry;
												CU_state <= write_reg;
												control_state <= 3;
										  when 3 =>
												ADDR <= tmp_read_addr;
												DATA <= (others=>'Z');
												RAM1_OE<='0';
												RAM1_WE<='1';
												CU_state <= write_reg;
												control_state <= 4;
										  when 4 =>
												RAM1_EN <= '0';
												RAM1_OE <= '1';
												RAM1_WE <= '1';
												tmp_data <= tmp_data xor DATA;
												tmp_addr(2 downto 0) <= rx;
												CU_state <= write_reg;
												control_state <= 5;
										  when 5 =>
												ADDR <= tmp_addr;
												DATA <= tmp_data;
												RAM1_WE<='0';
												RAM1_OE<='1';
												CU_state <= instruction_fetch;
												control_state <= 0;
										  when others =>
												null;
									 end case;
                        
                        when "10011" =>   --LW
                            RegDst <= "10";
                            RegWrite <= "001";
                            MemtoReg <= "01";
                            MemRead <= '0';
                            MemWrite <= '0';
									 case control_state is
										  when 0 =>
												RAM1_EN <= '0';
												RAM1_OE <= '1';
												RAM1_WE <= '1';
												tmp_addr <= "0000000000000000";
												tmp_read_addr <="0000000000000000";
												tmp_read_addr(2 downto 0) <= rx;
												CU_state <= write_reg;
												control_state <= 1;
										  when 1 =>
												ADDR <= tmp_read_addr;
												DATA <= (others=>'Z');
												RAM1_OE<='0';
												RAM1_WE<='1';
												CU_state <= mem_control;
												control_state <= 2;
										  
										  when 4 =>
												RAM1_EN <= '0';
												RAM1_OE <= '1';
												RAM1_WE <= '1';
												tmp_data <= DATA;
												tmp_addr(2 downto 0) <= ry;
												CU_state <= write_reg;
												control_state <= 5;
										  when 5 =>
												ADDR <= tmp_addr;
												DATA <= tmp_data;
												RAM1_WE<='0';
												RAM1_OE<='1';
												CU_state <= instruction_fetch;
												control_state <= 0;
										  when others =>
												null;
									 end case;

                        when "11011" =>   --SW
                            MemRead <= '0';
                            MemWrite <= '0';
                            IorD <= '0';
									 case control_state is
										  when 0 =>
												RAM1_EN <= '0';
												RAM1_OE <= '1';
												RAM1_WE <= '1';
												tmp_addr <= "0000000000000000";
												tmp_read_addr <="0000000000000000";
												tmp_read_addr(2 downto 0) <= ry;
												CU_state <= write_reg;
												control_state <= 1;
										  when 1 =>
												ADDR <= tmp_read_addr;
												DATA <= (others=>'Z');
												RAM1_OE<='0';
												RAM1_WE<='1';
												CU_state <= write_reg;
												control_state <= 2;
										  when 2 =>
												RAM1_EN <= '0';
												RAM1_OE <= '1';
												RAM1_WE <= '1';
												tmp_data <= DATA;
												tmp_read_addr <="0000000000000000";
												tmp_read_addr(2 downto 0) <= rx;
												CU_state <= write_reg;
												control_state <= 3;
										  when 3 =>
												ADDR <= tmp_read_addr;
												DATA <= (others=>'Z');
												RAM1_OE<='0';
												RAM1_WE<='1';
												CU_state <= mem_control;
												control_state <= 4;
										  
										  when others =>
												null;
									 end case;
								when others =>
									 null;
                    end case;
						 
					  
			end case;
		end if;
	end process;
    

    
                            
process(RST,clk0,State_show)

	begin
        if RST = '0' then
            tmp_light <= x"0000";
        elsif clk0'event and clk0 = '1' then
            tmp_light <= x"0000";
            case State_show is
                when PC =>
                    tmp_light (15) <= PcWrite;
                    tmp_light (11) <= PCSource;
                    tmp_light (7) <= PcWriteCond;
                when ALU =>
                    tmp_light (15 downto 14) <= ALUOp;
                    tmp_light (11) <= ALUSrcA;
                    tmp_light (7 downto 6) <= ALUSrcB;
                when M =>
                    tmp_light (15) <= MemRead;
                    tmp_light (11) <= MemWrite;
                    tmp_light (7) <= IRWrite;
                    tmp_light (3 downto 2) <= MemtoReg;
                when REG =>
                    tmp_light (15 downto 13) <= RegWrite;
                    tmp_light (11 downto 10) <= RegDst;
                    tmp_light (7) <= IorD;
            end case;
        end if;
    end process;
dbc <= '1';
OUTPUT <= tmp_light;
end Behavioral;

