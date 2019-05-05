
entity zegar is
end entity;

architecture klawiatura of zegar is
	-- declarative region
	signal sig : integer := 0;
begin
	process is
		variable var : integer := 0;
	begin
		report "***Process begin***";
		var := var + 1;
		sig <= sig + 1;
		report "Firstly, Variable: " & integer'image(var) & " Signal: " & integer'image(sig);

		var := var + 1;
		sig <= sig + 1;
		report "Before Wait, Variable: " & integer'image(var) & " Signal: " & integer'image(sig);

		wait for 10 ns;

		var := var + 1;
		sig <= sig + 1;
		report "After Wait, Variable: " & integer'image(var) & " Signal: " & integer'image(sig);

	end process;

end architecture;