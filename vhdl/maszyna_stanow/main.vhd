library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
 
entity maszyna_stanow is
 Port ( Clk : in  STD_LOGIC; -- sygnal zegarowy jest uzywany w bloku process odpowiadajacym za dzialanie naszej maszyny stanow
        DPSwitch : in  STD_LOGIC_VECTOR(1 downto 0); -- dwa przelaczniki DIP z ktorych korzystamy do poruszania sie pomiedzy stanami
        LED : out  STD_LOGIC_VECTOR(3 downto 0));  -- 4 diody LED jako wyjscia
end maszyna_stanow;
 
architecture Behavioral of maszyna_stanow is
 
-- ponizsza instrukcja definiuje nowy rodzaj sygnalu, ktory moze przyjac jedynie te wartosci 
-- ktore sa wymienione w nawiasie - konstrukcja ta jest podobna do definicji enum znanej z jezyka programowania C
type typ_stanu is (S0, S1, S2, S3);  -- Definiowanie stanow
 
signal Stan : typ_stanu := S0;    -- Tworzenie sygnalu - zmiennej mogacej przyjmowac wartosci zdefiniowane w State_Type;
 
begin
 
 
process (Clk) 
 
begin 
 
    if rising_edge(Clk) then    -- gdy nastapi narastajace zbocze sygnalu zegarowego
                                -- instrukcje zawarte ponizej beda wykonane
 
 
      -- Instrukcja CASE sprawdza wartosc sygnalu Stan,
      -- bazujac na jego wartosci jest wykonywany okreslony blok WHEN
      -- ktory jest wstanie zmienic wartosc sygnalu Stan.
      case Stan is
 
      -- Gdy obecny stan to S0 i przelacznik DIP nr 8 na plytce ElbertV2 jest w pozycji ON,
      -- to nastepny stan to S1;
      when S0 => 
         if (not DPSwitch(0)) = '1' then
            Stan <= S1;
         else
            Stan <= S0;
         end if; 
 
      -- Gdy obecny stan to S1 i przelacznik DIP nr 7 na plytce ElbertV2 jest w pozycji ON,
      -- to nastepny stan to S2; 
      when S1 => 
         if (not DPSwitch(1)) = '1' then 
            Stan <= S2;
         else
            Stan <= S1;
         end if; 
 
      -- Gdy obecny stan to S2 i przelacznik DIP nr 8 na plytce ElbertV2 jest w pozycji OFF,
      -- to nastepny stan to S3;
      when S2 => 
         if (not DPSwitch(0)) = '0' then 
            Stan <= S3;
         else
            Stan <= S2;
         end if; 
 
      -- Gdy obecny stan to S3 i przelacznik DIP nr 7 na plytce ElbertV2 jest w pozycji OFF,
      -- to nastepny stan to S0;
      when S3 => 
         if (not DPSwitch(1)) = '0' then 
            Stan <= S0;
         else
            Stan <= S3;
         end if; 
 
      -- Gdy wartosc sygnalu Stan obierze wartosc nieustalona to uklad przejdzie w stan S0;
      when others =>
         Stan <= S0;
   end case; 
 
  end if;
 
end process;
 
 
-- Ponizsze instrukcje przenosza wartosc stanu na diody LED
-- np. jesli sygnal Stan jest rowny S0 to wlaczy sie dioda LED0 (D8 na plytce ElbertV2);
LED(0) <= '1' WHEN Stan=S0 ELSE '0';
LED(1) <= '1' WHEN Stan=S1 ELSE '0';
LED(2) <= '1' WHEN Stan=S2 ELSE '0';
LED(3) <= '1' WHEN Stan=S3 ELSE '0';
 
end Behavioral;