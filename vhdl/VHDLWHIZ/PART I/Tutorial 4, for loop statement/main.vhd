
entity zegar is
end entity;

architecture klawiatura of zegar is
begin

	process is
	begin
		for i in 1 to 10 loop
			report "i=" & integer'image(i);
		end loop;
		wait;
	end process;

end architecture;