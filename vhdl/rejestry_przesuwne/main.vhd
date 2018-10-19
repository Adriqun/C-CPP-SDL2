library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity main is
	port(
		Clk : in STD_LOGIC;
		LED : out STD_LOGIC_VECTOR(7 downto 0)
	);
end main;

architecture Behavioral of main is
	signal slider : STD_LOGIC_VECTOR(7 downto 0) := X"01"; -- x - hex, b - binary
	constant COUNTER_LIMIT : integer := 12000000;
	signal counter : STD_LOGIC_VECTOR(24 downto 0);
begin
	-- ponizszy peoces jest wykonywany po kazdej zmianie sygnalu zegarowego
	counting : process(Clk)
		begin
			-- dla narastajacego zbocza sygnalu zegarowe
			if rising_edge(Clk) then
				if (counter = COUNTER_LIMIT) then
					counter <= (others => '0'); -- przypisz wszystkim bitom wartosc 0
					
					-- przeklejenie najmlodszego bitu na najstarsza pozycje
					 slider <= slider(0) & slider(7 downto 1);
					-- --------
				else
					counter <= counter + 1;
				end if;
			end if;
		end process counting;
	LED <= slider;
end Behavioral;

