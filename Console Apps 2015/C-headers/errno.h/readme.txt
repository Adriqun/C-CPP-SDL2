errno to makro przechowuj�ca kod ostatniego b��du.
Na pocz�tku dzia�ania programu ma warto�� 0 oznaczaj�c� brak problem�w.
Je�li w trakcie dzia�ania pojawi� si� b��dy
(na przyk�ad na skutek dzia�ania funkcji wej�cia/wyj�cia),
errno zostanie ustawione na warto�� m�wi�c� o przyczynie wyst�pienia b��du.
Funkcje ze standardowej biblioteki C nigdy nie zeruj� warto�ci tej zmiennej.

Standard C89 definiuje nast�puj�ce warto�ci zmiennej:
0 - brak b��du,
EDOM - b��d zakresu argument�w przy wywo�ywaniu funkcji matematycznych,
ERANGE - wynik dzia�ania funkcji matematycznych nie mie�ci si� w typie wyniku.

Dodatkowo, standard C99 definiuje warto��:
EILSEQ - napotkano b��dn� reprezentacj� wielobajtowego znaku.

Ponadto identyfikatory zaczynaj�ce si� od du�ej litery E,
po kt�rej nast�puje cyfra lub jaka� du�a litera s� zarezerwowane
dla implementacji do okre�lania innych mo�liwych b��d�w.