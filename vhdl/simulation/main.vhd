library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity logic_gates is
	port(
		switch : in STD_LOGIC_VECTOR(1 downto 0);
		LED : out STD_LOGIC_VECTOR(0 downto 0);
	);
end logic_gates;

architecture Behavioral of logic_gates is

begin
	LED(0) <= (not switch(0) and not switch(1));
end Behavioral;

