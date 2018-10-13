library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity my_and is
	port(
		switch : in STD_LOGIC_VECTOR(1 downto 0);
		LED : out STD_LOGIC_VECTOR(0 to 0)
	);
end my_and;


architecture Behavioral of my_and is
begin
	LED(0) <= (not switch(0)) and (not switch(1));
end Behavioral;

