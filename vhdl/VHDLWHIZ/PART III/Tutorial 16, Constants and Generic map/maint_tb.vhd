library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity GenericMuxTb is
end entity;

architecture RTL of GenericMuxTb is
	constant DataWidth : integer := 8;
	signal Sig1 : signed(DataWidth-1 downto 0) := x"AA";
	signal Sig2 : signed(DataWidth-1 downto 0) := x"BB";
	signal Sig3 : signed(DataWidth-1 downto 0) := x"CC";
	signal Sig4 : signed(DataWidth-1 downto 0) := x"DD";

	signal Sel : signed(1 downto 0) := "00";
	signal Output : signed(DataWidth-1 downto 0);
begin
	i_GenericMux : entity work.GenericMux(RTL)
	generic map(DataWidth => DataWidth)
	port map(
		Sel => Sel,
		Sig1 => Sig1,
		Sig2 => Sig2,
		Sig3 => Sig3,
		Sig4 => Sig4,
		Output => Output
		);

	process is
	begin
		wait for 10 ns;
		Sel <= Sel + 1;
		wait for 10 ns;
		Sel <= Sel + 1;
		wait for 10 ns;
		Sel <= Sel + 1;
		wait for 10 ns;
		Sel <= Sel + 1;
		wait for 10 ns;
		Sel <= "UU";
		wait;
	end process;
end architecture;