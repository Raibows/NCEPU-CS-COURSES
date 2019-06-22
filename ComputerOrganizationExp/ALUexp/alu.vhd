


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





entity alu is
    Port ( CLK : in  STD_LOGIC;
           RST : in  STD_LOGIC;
           INPUT : in  STD_LOGIC_VECTOR (15 downto 0);
           OUTPUT : out  STD_LOGIC_VECTOR (15 downto 0);
			  stateCnt: out STD_LOGIC_VECTOR (6 downto 0);
           Cin : in  STD_LOGIC;
           Cout : out  STD_LOGIC;
           Zout : out  STD_LOGIC);
end alu;

architecture Behavioral of alu is

signal state: integer range 0 to 3;
signal a, b,y: std_logic_vector(15 downto 0);	
signal opCode: std_logic_vector(3 downto 0);
signal zFlag, cFlag, sFlag, oFlag: std_logic;

begin

process(RST, CLK)
	begin
		if RST = '0' then state <= 0; a<="0000000000000000"; b<="0000000000000000"; opCode<="0000"; output <= (others=>'0'); stateCnt <= not "0000000";
		elsif CLK'event and CLK = '1' then
			case state is
			
				when 0 => state <= 1; a <= INPUT; stateCnt <= not "1000000";OUTPUT<=a;
				when 1 => state <= 2; b <= INPUT; stateCnt <= not "1111001";OUTPUT<=b;
				when 2 => state <= 3; opCode <= input(3 downto 0); stateCnt <= not "0100100"; OUTPUT <= input;
				when 3 => state <= 0; OUTPUT<= y; stateCnt <= not "0110000";
                
			end case;
		end if;
	end process;
	
process(RST, opCode)

	begin
			case opCode is
			when "0000"	=>	y<= a + b;
            when "0001"	=>	y<= a + (not b) + 1;
            when "0010" =>  y<= a and b;
            when "0011" =>  y<= a or b;
            when "0100" =>  y<= a xor b;
            when "0101" =>  y<= (not a) + 1;
            when "0110" =>  y<= TO_STDLOGICVECTOR((TO_BITVECTOR(a)) sll (CONV_INTEGER(b)));
            when "0111" =>  y<= TO_STDLOGICVECTOR((TO_BITVECTOR(a)) srl (CONV_INTEGER(b)));
            when "1000" =>  y<= TO_STDLOGICVECTOR((TO_BITVECTOR(a)) sra (CONV_INTEGER(b)));
            when "1001" =>  y<= TO_STDLOGICVECTOR((TO_BITVECTOR(a)) rol (CONV_INTEGER(b)));
			
	
			when others=> y<="0000000000000000";
		
		end case;
	end process;
	
end Behavioral;

