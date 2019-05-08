library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity Soup is
end entity;

architecture Spoon of Soup is
	signal Uns : unsigned(5 downto 0) := (others => '0');
	signal Mul1 : unsigned(7 downto 0) := (others => '0');
	signal Mul2 : unsigned(7 downto 0) := (others => '0');
	signal Mul3 : unsigned(7 downto 0) := (others => '0');
begin
	process is
	begin
		Uns <= Uns + 1;
		wait for 10 ns;
	end process;

	proc1 : process
	begin
		Mul1 <= Uns & "00";
		wait on Uns;
	end process;

	proc2 : process(Uns)
	begin
		Mul2 <= Uns & "00";
	end process proc2;

	-- Equivalent process using a concurrent statement.
	Mul3 <= Uns & "00";
end architecture;