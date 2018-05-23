errno to makro przechowuj¹ca kod ostatniego b³êdu.
Na pocz¹tku dzia³ania programu ma wartoœæ 0 oznaczaj¹c¹ brak problemów.
Jeœli w trakcie dzia³ania pojawi¹ siê b³êdy
(na przyk³ad na skutek dzia³ania funkcji wejœcia/wyjœcia),
errno zostanie ustawione na wartoœæ mówi¹c¹ o przyczynie wyst¹pienia b³êdu.
Funkcje ze standardowej biblioteki C nigdy nie zeruj¹ wartoœci tej zmiennej.

Standard C89 definiuje nastêpuj¹ce wartoœci zmiennej:
0 - brak b³êdu,
EDOM - b³¹d zakresu argumentów przy wywo³ywaniu funkcji matematycznych,
ERANGE - wynik dzia³ania funkcji matematycznych nie mieœci siê w typie wyniku.

Dodatkowo, standard C99 definiuje wartoœæ:
EILSEQ - napotkano b³êdn¹ reprezentacjê wielobajtowego znaku.

Ponadto identyfikatory zaczynaj¹ce siê od du¿ej litery E,
po której nastêpuje cyfra lub jakaœ du¿a litera s¹ zarezerwowane
dla implementacji do okreœlania innych mo¿liwych b³êdów.