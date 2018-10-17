library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity multi is
	port(
		switch : in STD_LOGIC_VECTOR(3 downto 0);
		dp_switch : in STD_LOGIC_VECTOR(1 downto 0);
		LED : out STD_LOGIC_VECTOR(0 downto 0)
	);
end multi;



architecture Behavioral of multi is
	signal inbuses : STD_LOGIC_VECTOR(3 downto 0); -- szyna buforowa wejsc
	signal adresses : STD_LOGIC_VECTOR(1 downto 0); -- szyna buforowa adresow
begin
	with adresses select
		LED(0) <= inbuses(0) when "00",
					 inbuses(1) when "01",
					 inbuses(2) when "10",
					 inbuses(3) when others;
					 
	-- Ponizej przypisanie wektorow (magistrali) wejsciowych do sygnalow lokalnych
	inbuses <= not switch; -- na raz przeprowadzana jest negacja wszystkich bitow danej zmiennej
	adresses <= not dp_switch;
end Behavioral;

