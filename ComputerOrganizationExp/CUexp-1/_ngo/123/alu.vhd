----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    09:49:51 06/23/2019 
-- Design Name: 
-- Module Name:    controller - Behavioral 
-- Project Name: 
-- Target Devices: 
-- Tool versions: a
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

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity controller is
    Port ( clk : in  STD_LOGIC;
           rst : in  STD_LOGIC;
           showCtrl : in  STD_LOGIC;
           bZero_ctrl : in  STD_LOGIC;
			  stateCnt: out STD_LOGIC_VECTOR (6 downto 0);
           INPUT : in  STD_LOGIC_VECTOR (15 downto 0);
           OUTPUT : out  STD_LOGIC_VECTOR (15 downto 0));
end controller;

architecture Behavioral of controller is
signal state:integer range 0 to 4;
signal bzero_state:integer range 0 to 1;
signal show_state:integer range 0 to 3;
signal instr:std_logic_vector(15 downto 0);
--signal opcode:std_logic_vector(4 downto 0);
--signal endtwo:std_logic_vector(1 downto 0);
signal to_output:std_logic_vector(15 downto 0);
signal RegDst:std_logic_vector(1 downto 0);
signal RegWrite:std_logic_vector(2 downto 0);
signal MemtoReg:std_logic_vector(1 downto 0);
signal ALUsrcA:std_logic_vector(0 downto 0);
signal ALUsrcB:std_logic_vector(1 downto 0);
signal ALUOp:std_logic_vector(1 downto 0);
		signal MemRead:std_logic_vector(0 downto 0);
		signal MemWrite:std_logic_vector(0 downto 0);
		signal IorD:std_logic_vector(0 downto 0);
		signal IRWrite:std_logic_vector(0 downto 0);
		signal PcWrite:std_logic_vector(0 downto 0);
		signal PCSource:std_logic_vector(0 downto 0);
		signal PcWriteCond:std_logic_vector(0 downto 0);
		signal opCode: std_logic_vector(4 downto 0);
		signal endtwo: std_logic_vector(1 downto 0);

		begin
process(RST, CLK)
	begin
		if RST = '0' then state <= 0; stateCnt <= not "1000000";									 --初始化
		RegDst <= "00";RegWrite <= "000";MemtoReg <= "00";ALUSrcA <="0";ALUSrcB <="01";ALUOp <= "00";
		MemRead <= "1";MemWrite <= "0";  IorD <= "0";     IRWrite <="1";PcWrite <="1"; PCSource<="0";
		elsif CLK'event and CLK = '1' then
			
			case state is			
				when 0 => state <= 1; instr <= INPUT;stateCnt <= not "1111001";  --取指周期
											 ALUSrcA <="0";ALUSrcB <="10";ALUOp <= "00";
											 MemRead <= "0";IRWrite <="0";PcWrite <="0";
				when 1 => state <= 2; stateCnt <= not "0100100";												 		 --译码周期
										 opcode(4 downto 0) <= instr(15 downto 11);
										 endtwo(1 downto 0) <= instr(1 downto 0);
											 if instr(15 downto 11) = "11100" then																			--执行周期de值
											    if instr(1 downto 0) = "01" then																			--ADDU
														ALUSrcA <="1";ALUSrcB <="00";ALUOp <= "00";
												 elsif instr(1 downto 0) = "11" then																		--SUBU 
														ALUSrcA <="1";ALUSrcB <="00";ALUOp <= "01";				
												 end if;
											 elsif instr(15 downto 11)="00100"then																			--BEQZ
												 ALUSrcA <="1";ALUOp <= "10";
											 elsif instr(15 downto 11)="11101"then																			
												 if instr(1 downto 0) ="00" then																				--JR
													ALUSrcA <="1";ALUOp <= "10";
												 elsif instr(1 downto 0) ="10" then																			--XOR
													ALUSrcA <="1";ALUSrcB <="00";ALUOp <= "10";
												 end if;							
											 elsif instr(15 downto 11) ="10011"then																		--LW
												 ALUSrcA <="1";ALUSrcB <="10";ALUOp <= "00";
											 elsif instr(15 downto 11) ="11011"then																		--SW
												 ALUSrcA <="1";ALUSrcB <="10";ALUOp <= "00";
											 end if;
				when 2 => state <= 3; stateCnt <= not "0110000"; 												 		  --执行周期
											 if instr(15 downto 11) = "10011" then																			--访存周期de值
												 RegWrite <= "000";MemRead <= "1";IorD <= "1";PcWrite <="0";										--LW
											 elsif instr(15 downto 11) ="11011" then																		
												 RegWrite <= "000";MemWrite <= "1";IorD <= "1";PcWrite <="0";										--SW
											 end if;
				when 3 => state <= 4; stateCnt <= not "0011001";														  --访存周期
											 if instr(15 downto 11) = "11100" then																			--写回周期de值
												 RegDst <= "01";RegWrite <= "001";MemtoReg <= "00";													--ADDU and SUBU
												 MemRead <= "0";MemWrite <= "0";																			
											 elsif instr(15 downto 11) ="11101"then																			
												 if instr(1 downto 0) ="10" then																				--XOR
													 RegDst <= "00";RegWrite <= "001";MemtoReg <= "00";										
													 MemRead <= "0";MemWrite <= "0";
												 end if;							
											 elsif instr(15 downto 11) ="10011"then																		--LW
												 RegDst <= "10";RegWrite <= "001";MemtoReg <= "01";										
												 MemRead <= "0";MemWrite <= "0";
											 elsif instr(15 downto 11) ="11011"then																		--SW
												 MemRead <= "0";MemWrite <= "0";IorD <="0";
											 end if;
				when 4 => state <= 0; stateCnt <= not "1000000";												 		  --写回周期
											 RegDst <= "00";RegWrite <= "000";MemtoReg <= "00";ALUSrcA <="0";ALUSrcB <="01";ALUOp <= "00";--取指周期de值
											 MemRead <= "1";MemWrite <= "0";  IorD <= "0";     IRWrite <="1";PcWrite <="1"; PCSource<="0";
			end case;
		end if;
	end process;

process(showCtrl,rst)
	begin
		if RST = '0' then show_state<= 0;to_output <= (others=>'0');output <= (others=>'0');
		elsif rising_edge(showCtrl) then																			 
			case show_state is
					when 0 => show_state <=1;--to_output(15 downto 0)<=(others=>'0');
													 to_output(15) <= PCWrite(0);
													 to_output(11) <= PCSource(0);
													 to_output(7)  <= PCWriteCond(0);
					when 1 => show_state <=2;--to_output(15 downto 0)<=(others=>'0');
													 to_output(15 downto 14) <= ALUOp(1 downto 0);
													 to_output(11) <= ALUSrcA(0);
													 to_output(7 downto 6)  <= ALUSrcB(1 downto 0);
					when 2 => show_state <=3;--to_output(15 downto 0)<=(others=>'0');
													 to_output(15) <= MemRead(0);
													 
													 to_output(11) <= MemWrite(0);
													 to_output(7)  <= IRWrite(0);
													 
													 to_output(3 downto 2) <= MemtoReg(1 downto 0);
					when 3 => show_state <=0;--to_output(15 downto 0)<=(others=>'0');
													 to_output(15 downto 13) <= RegWrite(2 downto 0);
													 
													 to_output(7)  <= IorD(0);
													 to_output(3 downto 2) <= "00";
			end case;
		 end if;
		 OUTPUT<=to_output;
	end process;	
end Behavioral;