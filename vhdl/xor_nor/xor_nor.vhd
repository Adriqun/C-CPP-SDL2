library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity xor_nor is
	port(
		switch : in STD_LOGIC_VECTOR(3 downto 0);
		LED : out STD_LOGIC_VECTOR(1 downto 0)
	);
end xor_nor;

architecture Behavioral of xor_nor is
begin
	-- XOR
	LED(0) <= ((not switch(0)) and (switch(1))) or
				 ((switch(0)) and (not switch(1)));
	-- NOR	 
	LED(1) <= switch(2) and switch(3);
end Behavioral;

