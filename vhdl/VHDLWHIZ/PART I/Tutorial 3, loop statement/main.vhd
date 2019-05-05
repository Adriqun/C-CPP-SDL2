
entity zegar is
end entity;

architecture klawiatura of zegar is
begin
	
	process is
	begin
		report "Hello!";
		loop
			report "Peekaboo!";
			exit;
		end loop;
		report "Goodbye!";
		wait;
	end process;

end architecture;