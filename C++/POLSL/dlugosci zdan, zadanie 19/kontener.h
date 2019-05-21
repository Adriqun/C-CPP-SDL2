#ifndef __KONTENER_H__
#define __KONTENER_H__

#include "zdanie.h"
#include <stdbool.h>

typedef struct Kontener
{
	unsigned char* wejscie;
	unsigned char* wyjscie;
	int statystyka[MAKSYMALNA_DLUGOSC_ZDANIA]; // reprezentuje ilosc zdan w danej komorce w tablicy
	Zdanie* zdania[MAKSYMALNA_DLUGOSC_ZDANIA];

	bool _i;	// -i <nazwa pliku wejsciowego>
	bool _o;	// -o <nazwa pliku wyjsciowego>
	bool _p;	// -p
} Kontener;

void przygotujKontener(Kontener *kontener);
bool sprawdzArgumenty(int ilosc, char*** argumenty, Kontener* kontener);
bool sprawdzPlik(Kontener* kontener);
void wykonaj(Kontener* kontener);

#endif