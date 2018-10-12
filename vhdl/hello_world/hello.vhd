----------------------------------------------------------------------------------
-- Company: None
-- Engineer: Adrian Michalek
-- 
-- Create Date:    20:03:35 10/11/2018 
-- Design Name: 
-- Module Name:    hello - Behavioral 
-- Project Name: Hello World
-- Target Devices: 
-- Tool versions: 
-- Description: 
--
-- Dependencies: 
--
-- Revision: 
-- Revision 0.01 - File Created
-- Additional Comments: My First VHDL Source
--
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;


-- Input & Output
entity hello is
	port(Clk : in STD_LOGIC; LED : out STD_LOGIC_VECTOR(7 DOWNTO 0));
end hello;



architecture Behavioral of hello is
	constant COUNTER_LIMIT : integer := 5000000; -- 5 sec?
	signal counter : unsigned (24 downto 0); 								-- Local signal with a 25 bit length
	signal blinking : STD_LOGIC_VECTOR (7 downto 0) := "00000000"; -- Local variable (8 bit length)
begin
	process(Clk) -- Process
		begin
		if rising_edge(Clk) then 		  -- For every rising edge
			if counter = COUNTER_LIMIT then
				counter <= b"0000000000000000000000000";
				blinking <= not blinking; -- Revert the state of all bits
			else
				counter <= counter + 1;
			end if;
		end if;
	end process;
	
	LED <= blinking;
end Behavioral;

