library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity Soup is
end entity;

architecture Spoon of Soup is
	signal UnsCnt : unsigned(7 downto 0) := (others => '0');
	signal SigCnt : signed(7 downto 0) := (others => '0');
	
	signal Uns4 : unsigned(3 downto 0) := "1000";
	signal Sig4 : signed(3 downto 0) := "1000";
	
	signal Uns8 : unsigned(7 downto 0) := (others => '0');
	signal Sig8 : signed(7 downto 0) := (others => '0');


begin
	process is
	begin
		wait for 10 ns;

		-- wrapping counter
		UnsCnt <= UnsCnt + 1;
		SigCnt <= SigCnt + 1;

		-- adding signals
		Uns8 <= Uns8 + Uns4;
		Sig8 <= Sig8 + Sig4;
	end process;
end architecture;