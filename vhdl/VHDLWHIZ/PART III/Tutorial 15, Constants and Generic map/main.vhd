library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity GenericMux is
	generic(DataWidth : integer);
	port(
			-- Inputs
			Sig1 : in signed(DataWidth-1 downto 0);
			Sig2 : in signed(DataWidth-1 downto 0);
			Sig3 : in signed(DataWidth-1 downto 0);
			Sig4 : in signed(DataWidth-1 downto 0);

			-- Selector
			Sel : in signed(1 downto 0);

			-- Outputs
			Output : out signed(DataWidth-1 downto 0)
		);
end entity;

architecture RTL of GenericMux is
begin
	process(Sel, Sig1, Sig2, Sig3, Sig4) is
	begin
		case Sel is
			when "00" =>
				Output <= Sig1;
			when "01" =>
				Output <= Sig2;
			when "10" =>
				Output <= Sig3;
			when "11" =>
				Output <= Sig4;
			when others => -- 'U', 'X', '-'
				Output <= (others => 'X');
		end case;
	end process;
end architecture;