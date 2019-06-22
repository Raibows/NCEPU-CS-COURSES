


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

signal state: integer range 0 to 4;
signal a, b,y: std_logic_vector(15 downto 0);	
signal opCode: std_logic_vector(3 downto 0);
signal zFlag, vFlag, cFlag, sFlag, oFlag: std_logic; --cflag is ½øÎ» vflag is Òç³ö zflag is zero sflg is signal flag
signal judge: std_logic_vector(15 downto 0);
signal temp2,temp3,temp4: integer range 0 to 15;
signal temp1: std_logic;
begin

process(RST, CLK)
	begin
		if RST = '0' then state <= 0; a<="0000000000000000"; b<="0000000000000000"; opCode<="0000"; output <= (others=>'0'); stateCnt <= not "0000000";
		elsif CLK'event and CLK = '1' then
			case state is
				when 0 => state <= 1; a <= INPUT; stateCnt <= not "1000000";OUTPUT<=a;
				when 1 => state <= 2; b <= INPUT; stateCnt <= not "1111001";OUTPUT<=b;
				when 2 => state <= 3; opCode <= input(3 downto 0); stateCnt <= not "0100100"; OUTPUT <= input;
				when 3 => state <= 4; OUTPUT<= y; stateCnt <= not "0110000";
				when 4 => state <= 0; OUTPUT<= judge; stateCnt <= not "0011001";
			end case;
		end if;
	end process;
	
process(RST, opCode)
	begin
			case opCode is
            when "0000"	=>	y<= a + b; judge <= "0000000000000000";vFlag <= '0';cFlag <= '0';sFlag <= '0';zFlag <= '0'; --default positive
            case y(15) is
                when '1' => vFlag <= '1';  --judge overflow
                when others => vFlag <= '0';
            end case;
            if vFlag = '0' then --judge carrier
                cFlag <= '0';
                for i in 14 to 0 loop
                    temp1 <= (a(i) or b(i));
                    if temp1 = '1' then temp2 <= i;temp1 <= '0';
                    end if;
                end loop;
                for i in 14 to 0 loop
                    if y(i) = '1' then temp3 <= i;
                    end if;
                end loop;
                if temp3 > temp2 then
                    temp3 <= 0;
                    temp2 <= 0;
                    cFlag <= '1';
                end if ;
            end if;
            
            if y = "0000000000000000" then  --judege all zero
                zFlag <= '1';
                cFlag <= '1';
            else
                zFlag <= '0';
            end if;

            if y(15) = '1' then 
                    sFlag <= '1';
                else
                    sFlag <= '0';
            end if;
            
            if vFlag = '1' then
                judge(15) <= vFlag; --overflow
            else
                judge(14) <= cFlag; --carrier
                judge(13) <= zFlag; --all zero
                judge(12) <= sFlag; --signal
            end if;
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

