#ifndef __ZDANIE_H__
#define __ZDANIE_H__

typedef struct Zdanie
{
	char* tekst;
	int poczatek_wiersz;	// wiersz w ktorym rozpoczyna sie zdanie
	int koniec_wiersz;		// wiersz w ktorym konczy sie zdanie
	long int iloscWyrazow;
	long int iloscInterpunkcyjnych;
	struct Zdanie* nastepny;
} Zdanie;

#define MAKSYMALNA_DLUGOSC_ZDANIA 5000
#endif