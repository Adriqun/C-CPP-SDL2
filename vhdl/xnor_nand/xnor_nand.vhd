library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity xnor_nand is
	port(
		switch : in STD_LOGIC_VECTOR(1 downto 0);
		dip : in STD_LOGIC_VECTOR(0 downto 0);
		LED : out STD_LOGIC_VECTOR(0 downto 0)
	);
end xnor_nand;


architecture Behavioral of xnor_nand is
	signal buttons : STD_LOGIC_VECTOR(1 downto 0);
	signal adresses : STD_LOGIC_VECTOR(0 downto 0);
begin
	with adresses select
		LED(0) <= (buttons(0) nand buttons(1)) when "0",
					 (buttons(0) xnor buttons(1)) when others;
	buttons <= not switch;
	adresses <= not dip;
end Behavioral;

