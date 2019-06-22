--------------------------------------------------------------------------------
-- Company: 
-- Engineer:
--
-- Create Date:   19:59:20 05/18/2019
-- Design Name:   
-- Module Name:   C:/Users/Raibows/Desktop/2 ALU/testalu.vhd
-- Project Name:  aluzdy
-- Target Device:  
-- Tool versions:  
-- Description:   
-- 
-- VHDL Test Bench Created by ISE for module: alu
-- 
-- Dependencies:
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
--
-- Notes: 
-- This testbench has been automatically generated using types std_logic and
-- std_logic_vector for the ports of the unit under test.  Xilinx recommends
-- that these types always be used for the top-level I/O of a design in order
-- to guarantee that the testbench will bind correctly to the post-implementation 
-- simulation model.
--------------------------------------------------------------------------------
LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
 
-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--USE ieee.numeric_std.ALL;
 
ENTITY testalu IS
END testalu;
 
ARCHITECTURE behavior OF testalu IS 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    COMPONENT alu
    PORT(
         CLK : IN  std_logic;
         RST : IN  std_logic;
         INPUT : IN  std_logic_vector(15 downto 0);
         OUTPUT : OUT  std_logic_vector(15 downto 0);
         stateCnt : OUT  std_logic_vector(6 downto 0);
         Cin : IN  std_logic;
         Cout : OUT  std_logic;
         Zout : OUT  std_logic
        );
    END COMPONENT;
    

   --Inputs
   signal CLK : std_logic := '0';
   signal RST : std_logic := '0';
   signal INPUT : std_logic_vector(15 downto 0) := (others => '0');
   signal Cin : std_logic := '0';

 	--Outputs
   signal OUTPUT : std_logic_vector(15 downto 0);
   signal stateCnt : std_logic_vector(6 downto 0);
   signal Cout : std_logic;
   signal Zout : std_logic;

   -- Clock period definitions
   constant CLK_period : time := 10 ns;
 
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
   uut: alu PORT MAP (
          CLK => CLK,
          RST => RST,
          INPUT => INPUT,
          OUTPUT => OUTPUT,
          stateCnt => stateCnt,
          Cin => Cin,
          Cout => Cout,
          Zout => Zout
        );

  process
  begin
		rst<='0';
		wait for 100 ns;
		rst<='1';
		wait for 1 ms;
  end process;	
	
  process
  begin
		clk<='0';
		wait for 20 ns;
		clk<='1';
		wait for 20 ms;
  end process;		

END;
