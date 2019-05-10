-- Summary for tutorials 1-5
-- 1. Declaring processes.
-- 2. Report Statements.
-- 3. wait; and wait for <time> <time units> syntax.
-- 4. variable of type integer use.
-- 5. loop, for loop and while statements.

-- Testbench
entity Tb is
end entity;

-- Architecture
architecture Sim of Tb is
begin
	p1 : process is
	begin
		report "P1: Hello World";
		wait; -- Wait forever. This process will be executed once.
	end process;

	p2 : process is
	begin
		report "P2: Hello";
		wait for 10 ns; -- This process will be executed every 10 nano seconds.
	end process;

	p3 : process is
	begin
		report "P3: Loop";
		loop
			report "P3: Hello from loop";
			exit; -- Exit loop
		end loop;
		wait; -- Wait forever.
	end process;
	
	p4 : process is
		variable var : integer := 0; -- Declare variable
	begin
		for i in 10 downto 0 loop
			report "P4: var = " & integer'image(var);
			var := var + 1;
			report "P4: i = " & integer'image(i);
		end loop;
		wait;
	end process;

	p5 : process is
		variable var : integer := 5;
	begin
		while var > 0 loop
			report "P5: var = " & integer'image(var);
			var := var - 1;
		end loop;
		wait;
	end process;
end architecture;