-- Summary for tutorials 5-11
-- 1. Difference between signals and variables (signals are updated after wait statement in processes)
-- 2. wait for, wait until, wait on
-- 3. Sensivity list.
-- 4. If , elsif, else statement.
-- 5. std_logic and waveform (in modelsim)
-- 6. std_logic_vector and shifting

entity Tb is
end entity;

architecture ASim of Tb is
	signal sig : integer := 0;
	signal CountUp : integer := 0;
	signal CountDown : integer := 0;
begin
	process is
		variable var : integer := 0;
	begin
		report "**Start**";
		var := var + 1;
		sig <= sig + 1;
		report "1. var=" & integer'image(var) & " sig=" & integer'image(sig);

		var := var + 1;
		sig <= sig + 1;
		report "2. var=" & integer'image(var) & " sig=" & integer'image(sig);

		wait for 10 ns;
		var := var + 1;
		sig <= sig + 1;
		report "3. var=" & integer'image(var) & " sig=" & integer'image(sig);
	end process;

	-- wait for
	p1 : process is
	begin
		CountUp <= CountUp + 1;
		CountDown <= CountDown - 1;
		wait for 10 ns;
	end process;

	-- wait on
	p2 : process is
	begin
		wait on CountUp, CountDown; -- will wait for CountUp and CountDown for change
		report "CountUp: " & integer'image(CountUp) & " CountDown: " & integer'image(CountDown);
		if CountUp > CountDown then
			report "CountUp is larger";
		elsif CountUp < CountDown then
			report "CountDown is larger";
		end if;
	end process;

	-- wait until
	p3 : process is
	begin
		wait until CountUp = CountDown;
		report "A Jackpot!";
	end process;

	-- sensivity list
	p4 : process(CountUp, CountDown) is
	begin
		if CountUp = CountDown then
			report "B Jackpot!";
		end if;
	end process;
end architecture;

library ieee;
use ieee.std_logic_1164.all;

architecture BSim of Tb is
	signal sig1 : std_logic := '0';
	signal sig2 : std_logic;
	signal sig3 : std_logic;

	signal slv1 : std_logic_vector(7 downto 0);
	signal slv2 : std_logic_vector(7 downto 0) := (others => '0');
	signal slv3 : std_logic_vector(7 downto 0) := (others => '1');
	signal slv4 : std_logic_vector(7 downto 0) := x"AA";
	signal slv5 : std_logic_vector(0 to 7) := "10101010";
	signal slv6 : std_logic_vector(7 downto 0) := "00000001";
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

	process is
	begin
		wait for 10 ns;
		for i in (slv6'left) downto (slv6'right + 1) loop
			slv6(i) <= slv6(i-1);
		end loop;
		slv6(slv6'right) <= slv6(slv6'left);
	end process;
end architecture;