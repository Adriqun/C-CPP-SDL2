LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
 
 
ENTITY test_bench IS
END test_bench;
 
ARCHITECTURE behavior OF test_bench IS 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    COMPONENT podstawowe_bramki
    PORT(
         Switch : IN  std_logic_vector(1 downto 0);
         LED : OUT  std_logic_vector(0 downto 0)
        );
    END COMPONENT;
    
 
   --Inputs
   signal Switch : std_logic_vector(1 downto 0) := (others => '0');
 
 --Outputs
   signal LED : std_logic_vector(0 downto 0);
   -- No clocks detected in port list. Replace <clock> below with 
   -- appropriate port name 
 
   constant period : time := 10 ns;
 
BEGIN
 
 -- Instantiate the Unit Under Test (UUT)
   uut: podstawowe_bramki PORT MAP (
          Switch => Switch,
          LED => LED
        );
 
   -- Stimulus process
   stim_proc: process
   begin 
      -- insert stimulus here 
      wait for 50 ns;
      Switch(0) <= '0';
      Switch(1) <= '0';
       
      wait for period;
      Switch(0) <= '1';
      Switch(1) <= '0';
       
      wait for period;
      Switch(0) <= '0';
      Switch(1) <= '1';
       
      wait for period;
      Switch(0) <= '1';
      Switch(1) <= '1';
      wait;
   end process;
 
END;