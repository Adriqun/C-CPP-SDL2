library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;


entity myand is
	port(
	switch : in STD_LOGIC_VECTOR(1 downto o);
	LED : out STD_LOGIC_VECTOR(0 to 0)
	);
end myand;

architecture Behavioral of myand is
begin
	LED(0) <= (not switch(0)) and (not switch(1));
end Behavioral;

