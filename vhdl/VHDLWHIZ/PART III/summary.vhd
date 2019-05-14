-- Summary for tutorials 12-14
-- 1. Difference between signed and unsigned std_logic_vector
-- 2. Concurrent statements (instead of wait statement)
-- 3. Case-When statement

entity Tb is
end entity;

architecture ASim of Tb is
	signal Uns5 : unsigned(5 downto 0) := (others => '0');
	signal Mul8 : unsigned(7 downto 0) := (others => '0');

	signal Sig1 : unsigned(7 downto 0) := x"AA";
	signal Sig2 : unsigned(7 downto 0) := x"BB";
	signal Sig3 : unsigned(7 downto 0) := x"CC";
	signal Sig4 : unsigned(7 downto 0) := x"DD";
	signal Sel : unsigned(1 downto 0) := (others => '0');
	signal Output1 : unsigned(7 downto 0);
	signal Output2 : unsigned(7 downto 0);
begin

	-- negative values are different
	proc1 : process is
		signal Uns4 : unsigned(3 downto 0) := "1000";
		signal Sig4 : signed(3 downto 0) := "1000"; -- negative value
		signal Uns8 : unsigned(7 downto 0) := (others => '0');
		signal Sig8 : signed(7 downto 0) := (others => '0');
	begin
		wait for 10 ns;
		Uns8 <= Uns8 + Uns4;
		Sig8 <= Sig8 + Sig4;
	end process;

	proc2 : process is
	begin
		Uns5 <= Uns5 + 1;
		wait for 10 ns;
	end process;
	-- Equivalent process using a concurrent statement.
	Mul8 <= Uns5 & "00";

	-- Stimuli for the selector signal
	process is
	begin
		wait for 10 ns;
		Sel <= Sel + 1;
		wait for 10 ns;
		Sel <= Sel + 1;
		wait for 10 ns;
		Sel <= Sel + 1;
		wait for 10 ns;
		Sel <= Sel + 1;
		wait for 10 ns;
		Sel <= "UU";
		wait;
	end process;

	-- No Case-When Statement
	proc : process(Sel, Sig1, Sig2, Sig3, Sig4) is
	begin
		if Sel = "00" then
			Output1 <= Sig1;
		elsif Sel = "01" then
			Output1 <= Sig2;
		elsif Sel = "10" then
			Output1 <= Sig3;
		elsif Sel = "11" then
			Output1 <= Sig4;
		else
			Output1 <= (others => 'X');
		end if;
	end process;

	-- Case-When Statement
	process(Sel, Sig1, Sig2, Sig3, Sig4) is
	begin
		case Sel is
			when "00" =>
				Output2 <= Sig1;
			when "01" =>
				Output2 <= Sig2;
			when "10" =>
				Output2 <= Sig3;
			when "11" =>
				Output2 <= Sig4;
			when others => -- 'U', 'X', '-'
				Output2 <= (others => 'X');
		end case;
	end process;
end architecture;
