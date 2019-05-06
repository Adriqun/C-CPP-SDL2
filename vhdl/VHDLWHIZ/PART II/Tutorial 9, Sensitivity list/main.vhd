
entity Computer is
end entity;

architecture Mouse of Computer is
	signal CountUp : integer := 0;
	signal CountDown : integer := 10;

	procedure prt (signal a : in integer) is
	begin
		report a'PATH_NAME;
	end procedure prt;
begin
	blck : block
	begin
		process is
		begin
			prt(CountUp);
			CountUp <= CountUp + 1;
			CountDown <= CountDown - 1;
			wait for 10 ns;
		end process;
	end block;

	process is
	begin
		if CountUp = CountDown then
			report "A Jackpot";
		end if;
		wait on CountUp, CountDown;
	end process;

	process(CountUp, CountDown) is
	begin
		if CountUp = CountDown then
			report "B Jackpot!";
		end if;
	end process;

end architecture;