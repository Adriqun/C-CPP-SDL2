library IEEE;
use IEEE.std_logic_1164.all;

entity Computer is
end entity;

architecture Arch of Computer is
	signal sig1 : std_logic := '0';
	signal sig2 : std_logic;
	signal sig3 : std_logic;
begin
	process is
	begin
		
		wait for 10 ns;
		sig1 <= not sig1;
	end process;

	-- Driver A
	process is
	begin
		sig2 <= 'Z';
		sig3 <= '0';
		wait;
	end process;

	-- Driver B
	process(sig1) is
	begin
		if sig1 = '0' then
			sig2 <= 'Z';
			sig3 <= 'Z';
		else
			sig2 <= '1';
			sig3 <= '1';
		end if;
	end process;
end architecture;