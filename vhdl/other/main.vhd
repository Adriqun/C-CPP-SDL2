library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity Ent is
end entity;

architecture Arch of Ent is
begin
	process is
		variable sig : integer := 0;
	begin
		sig := integer'value("15.4"); -- error
		report "sig: " & integer'image(sig);
		wait;
	end process;
end architecture;
