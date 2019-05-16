entity Ent is
end entity;

architecture Arch of Ent is
	signal x : integer := 1;
	signal y : integer := 2;
	signal z : integer := 0;
begin
	-- sensitivity list
	process(x, y)	-- change of x or y will execute this process
	begin
		z <= x + y;
	end process;

	-- the same operation as above
	z <= x + y;

end architecture;