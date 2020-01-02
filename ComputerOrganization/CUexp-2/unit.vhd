----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    18:49:29 07/03/2019 
-- Design Name: 
-- Module Name:    unit - Behavioral 
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
-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;
-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;
entity unit is
	Port (rst : in STD_LOGIC;
			clk : in STD_LOGIC;
				clk0 : in STD_LOGIC;
			instructions : in STD_LOGIC_VECTOR (15 downto 0);
			light : out STD_LOGIC_VECTOR (15 downto 0);
				showCtrl : in std_logic;
				bZero_ctrl : in std_logic);
end unit;
architecture Behavioral of unit is
	signal bzero : std_logic;
	type shower_state is (PC,ALU,Mem,Reg);
	signal shower : shower_state;
	type controler_state is
	(instruction_fetch,decode,execute,mem_control,write_reg);
	signal state : controler_state;
	signal PCWrite : std_logic;
	signal PCWriteCond : std_logic;
	signal PCSource : std_logic;
	signal ALUOp : std_logic_vector(1 downto 0);
	signal ALUSrcA : std_logic;
	signal ALUSrcB : std_logic_vector(1 downto 0);
	signal MemRead : std_logic;
	signal MemWrite : std_logic;
	signal IRWrite : std_logic;
	signal MemtoReg : std_logic_vector(1 downto 0);
	signal RegWrite : std_logic_vector(2 downto 0);
	signal RegDst : std_logic_vector(1 downto 0);
	signal IorD : std_logic;
	signal tmpb_zero : std_logic;
	signal tmp_light : std_logic_vector(15 downto 0);
begin
light <= tmp_light;
process(clk,rst,showCtrl)
begin
	if rst='0' then
		shower<=PC;
	elsif rising_edge(showCtrl) then
		case shower is
			when PC=>
				shower<=ALU;
			when ALU=>
				shower<=Mem;
			when Mem=>
				shower<=Reg;
			when Reg=>
				shower<=PC;
		end case;
	end if;
end process;
process(clk0,rst,state)
begin
	if rst='0' then
		tmp_light<=x"0000";
	elsif rising_edge(clk0) then
		case shower is
			when PC=>
				tmp_light(15 downto 0)<=x"0000";
				tmp_light(15)<=PCWrite;
				tmp_light(11)<=PCSource;
				tmp_light(7)<=PCWriteCond;
			when ALU=>
				tmp_light(15 downto 0)<=x"0000";
				tmp_light(15 downto 14)<=ALUOp;
				tmp_light(11)<=ALUSrcA;
				tmp_light(7 downto 6)<=ALUSrcB;
			when Mem=>
				tmp_light(15 downto 0)<=x"0000";
				tmp_light(15)<=MemRead;
				tmp_light(11)<=MemWrite;
				tmp_light(7)<=IRWrite;
				tmp_light(3 downto 2)<=MemtoReg;
			when Reg=>
				tmp_light(15 downto 0)<=x"0000";
				tmp_light(15 downto 13)<=RegWrite;
				tmp_light(11 downto 10)<=RegDst;
				tmp_light(7)<=IorD;
		end case;
	end if;
end process;
process(rst,bzero_Ctrl)
begin 
		if rst = '0' then
			bzero<='0';
		elsif rising_edge (bzero_Ctrl) then
			if bzero <= '0' then
				bzero <= '1';
				tmpb_zero<='0';
			elsif bzero = '1' then 
				tmpb_zero<='1';
				bzero<='0';
			end if;
		end if;
end process;
process (bzero)
begin 
	if bzero = '1' then
		PCWriteCond<='1';
	elsif bzero = '0' then
		PCWriteCond<='0';
	end if;
end process;
process (rst,clk)
begin 
	if(rst = '0') then
		state<=instruction_fetch;
		IorD<='0';
		IRWrite<='0';
		MemRead<='0';
		MemWrite<='0';
		MemtoReg<="00";
		ALUOp<="00";
		ALUSrcA<='0';
		ALUSrcB<="00";
		PCWrite<='0';
		PCSource<='0';
		RegDst<="00";
		RegWrite<="000";
		elsif rising_edge (clk) then
			case state is
				when instruction_fetch=>
					MemRead<='1';
					ALUSrcA<='0';
					IorD<='0';
					ALUSrcB<="01";
					ALUOp<="00";
					PCWrite<='1';
					PCSource<='0';
					IRWrite<='1';
					RegWrite<="000";
					state<=decode;
				when decode=>
					IRWrite<='0';
					MemRead<='0';
					PCWrite<='0';
					ALUSrcA<='0';
					ALUSrcB<="10";
					ALUOp<="00";
					state<=execute;
				when execute=>
					case instructions(15 downto 11) is
						when "00100" =>
							ALUSrcA<='1';
							ALUOp<="10";
							PCSource<='1';
							state<=instruction_fetch;
						when "10011"=>
							ALUSrcA<='1';
							ALUSrcB<="10";
							ALUOp<="00";
							state<=mem_control;
						when "11011"=>
							ALUSrcA<='1';
							ALUSrcB<="10";
							ALUOp<="00";
							state<=mem_control;
						when "11100" =>
							case instructions (1 downto 0) is
								when "01" =>    -----addu
									ALUSrcA<='1';
									ALUSrcB<="00";
									ALUOp<="00"; 
								when "11" =>     -----subu
									ALUSrcA<='1';
									ALUSrcB<="00";
									ALUOp<="01";
								when others =>
									null;
							end case;
							state <=write_reg;
						when "11101" =>
							case instructions(4 downto 0) is
								when "01101" =>
									ALUSrcA<='1';
									ALUSrcB<="00";
									ALUOp<="10";
									state<=write_reg;
								when "00000" =>
									case instructions(7 downto 5) is
										when "000"=>
											ALUSrcA<='1';
											ALUOp<="10";
											PCWrite<= '1';
											PCSource <= '0';
											state<= instruction_fetch;
										when others=>
											null;
									end case;
								when others =>
									null;
							end case;
							when others=>
								null;
						end case;
					when mem_control =>
						PCWrite<= '0';
						RegWrite<="000";
						case instructions(15 downto 11) is
							when "10011" =>
								MemRead <= '1';
								IorD <= '1';
								state <= write_reg;
							when "11011" =>
								MemWrite <= '1';
								IorD <= '1';
								state <= write_reg;
							when others =>
								null;
						end case;
					when write_reg=>
						Memwrite <= '0';
						MemRead <= '0';
						case instructions (15 downto 11) is
							when "10011" =>
							RegDst <= "10";
							RegWrite <= "001";
							MemtoReg <= "01";
						when "11011" =>
							MemWrite <= '0';
							IorD <= '0';
						when "11100" =>
							case instructions (1 downto 0) is
								when "01" =>
									RegDst<= "01";
									RegWrite<= "001";
									MemtoReg <= "00";
								when "11" =>
									RegDst <="01";
									RegWrite<= "001";
									MemtoReg <= "00";
								when others =>
									null;
							end case;
						when "11101" =>
							case instructions (4 downto 0) is
								when "01101"=>
									RegDst <="00";
									RegWrite<= "001";
									MemtoReg <= "00";
								when others =>
									null;
							end case;
						when others=>
							null;
					end case;
					state <= instruction_fetch;
				end case;
			end if;
		end process;
end Behavioral;
