#include "kontener.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

bool sprawdzArgumenty(int ilosc, char*** argumenty, Kontener* kontener)
{
	char** argv = *argumenty;
	if (ilosc < 3)
	{
		printf("Blad, za mala liczba argumentow!\n");
		return false;
	}

	for (int i = 1; i < ilosc; ++i)
	{
		if (!strcmp(argv[i], "-i"))
		{
			if (kontener->_i)
			{
				printf("Blad, -i moze zostac uzyte tylko raz!\n");
				return false;
			}
			kontener->_i = true;
			if (++i >= ilosc)
			{
				printf("Blad, brakuje nazwy pliku dla -i!\n");
				return false;
			}
			int len = strlen(argv[i]);
			kontener->wejscie = (char*)malloc(len + 1);
			strncpy(kontener->wejscie, argv[i], len);
			kontener->wejscie[len] = '\0';
		}
		else if (!strcmp(argv[i], "-o"))
		{
			if (kontener->_o)
			{
				printf("Blad, -o moze zostac uzyte tylko raz!\n");
				return false;
			}
			kontener->_o = true;
			if (++i >= ilosc)
			{
				printf("Blad, brakuje nazwy pliku dla -o!\n");
				return false;
			}
			int len = strlen(argv[i]);
			kontener->wyjscie = (char*)malloc(len + 1);
			strncpy(kontener->wyjscie, argv[i], len);
			kontener->wyjscie[len] = '\0';
		}
		else if (!strcmp(argv[i], "-p"))
		{
			if (kontener->_p)
			{
				printf("Blad, -p moze zostac uzyte tylko raz!\n");
				return false;
			}
			kontener->_p = true;
		}
	}

	return true;
}


void przygotujKontener(Kontener *kontener)
{
	kontener->_i = false;
	kontener->_o = false;
	kontener->_p = false;

	kontener->wejscie = NULL;
	kontener->wyjscie = NULL;

	int i = 0;
	for (int i = 0; i < MAKSYMALNA_DLUGOSC_ZDANIA; i++)
	{
		kontener->statystyka[i] = 0;
		kontener->zdania[i] = NULL;
	}
}


bool sprawdzPlik(Kontener* kontener)
{
	FILE* plik = fopen(kontener->wejscie, "r");
	if (!plik)
	{
		printf("Blad, nie mozna otworzyc pliku %s\n", kontener->wejscie);
		return false;
	}

	for (int i = 0; i < MAKSYMALNA_DLUGOSC_ZDANIA; ++i)
		kontener->statystyka[i] = 0;
	
	
	char ch;
	char bufor[MAKSYMALNA_DLUGOSC_ZDANIA];
	int nr_wiersza = 1, startWiersza = 1;
	int dlugosc = 0;
	char poprzedniZnak = -1;
	long int iloscWyrazow = 0;
	long int iloscInterpunkcyjnych = 0;

	while (ch = fgetc(plik))
	{
		if ((ch == '.' || ch == EOF) && dlugosc)
		{	// koniec zdania
			char* tymczasowy = (char*)malloc(dlugosc + 1);
			for (int i = 0; i < dlugosc; ++i)
				tymczasowy[i] = bufor[i];
			tymczasowy[dlugosc] = '\0';
			++kontener->statystyka[dlugosc];

			Zdanie** pZdanie = &kontener->zdania[dlugosc];
			// idziemy na koniec listy
			while (*pZdanie)
				pZdanie = &(*pZdanie)->nastepny;

			// taktujemy kazde zdanie jako unikatowe
			*pZdanie = (Zdanie*)malloc(sizeof(Zdanie));
			(*pZdanie)->tekst = tymczasowy;
			(*pZdanie)->poczatek_wiersz = startWiersza;
			(*pZdanie)->koniec_wiersz = nr_wiersza;
			(*pZdanie)->iloscWyrazow = iloscWyrazow + 1;
			(*pZdanie)->iloscInterpunkcyjnych = iloscInterpunkcyjnych;
			(*pZdanie)->nastepny = NULL;

			// wyczysc
			dlugosc = 0;
			iloscWyrazow = 0;
			iloscInterpunkcyjnych = 0;
			startWiersza = nr_wiersza;
		}
		else
		{
			if (poprzedniZnak != ' ' && ch == ' ')
			{	// traktujemy jako nowy wyraz
				iloscWyrazow += 1;
			}
			else if (poprzedniZnak == '.' && ch == '\n')
			{
				++startWiersza;
				++nr_wiersza;
				poprzedniZnak = ch;
				continue;
			}
			else if (ch == '\n')
			{	// nowy numer wiersza
				nr_wiersza += 1;
			}
			else if (!isdigit(ch) && !isalpha(ch))
			{	// traktujemy jako znak interpunkcyjny
				iloscInterpunkcyjnych += 1;
			}

			bufor[dlugosc] = ch;
			++dlugosc;
			if (dlugosc >= MAKSYMALNA_DLUGOSC_ZDANIA)
			{
				printf("Blad maksymalna dlugosc zdania to %d\n", MAKSYMALNA_DLUGOSC_ZDANIA);
				fclose(plik);
				return false;
			}
		}

		poprzedniZnak = ch;
		if (ch == EOF)
			break;
	}

	fclose(plik);
	return true;
}


void wykonaj(Kontener* kontener)
{
	if (kontener->_p)
	{
		printf("Statystyka Zdan, Zdania posortowane na podstawie ich dlugosci:\n\n");
		for (int i = 0; i < MAKSYMALNA_DLUGOSC_ZDANIA; ++i)
			if (kontener->statystyka[i])
			{
				printf("*** %d zdan o dlugosci %d*** \n", kontener->statystyka[i], i);
				Zdanie* pZdanie = kontener->zdania[i];
				while (pZdanie)
				{
					printf("Wiersz %d-%d Ilosc wyrazow: %d Ilosc Znakow Interpunkcyjnych: %d: \n%s.\n", pZdanie->poczatek_wiersz,
						pZdanie->koniec_wiersz, pZdanie->iloscWyrazow, pZdanie->iloscInterpunkcyjnych, pZdanie->tekst);
					pZdanie = pZdanie->nastepny;
				}
				printf("\n");
			}
	}

	if (kontener->_o)
	{
		FILE* plik = fopen(kontener->wyjscie, "w");
		if (!plik)
			printf("Blad, nie mozna otworzyc pliku %s\n", kontener->wyjscie);
		else
		{
			fprintf(plik, "Statystyka Zdan, Zdania posortowane na podstawie ich dlugosci:\n\n");
			for (int i = 0; i < MAKSYMALNA_DLUGOSC_ZDANIA; ++i)
				if (kontener->statystyka[i])
				{
					fprintf(plik, "*** %d zdan o dlugosci %d*** \n", kontener->statystyka[i], i);
					Zdanie* pZdanie = kontener->zdania[i];
					while (pZdanie)
					{
						fprintf(plik, "Wiersz %d-%d Ilosc wyrazow: %d Ilosc Znakow Interpunkcyjnych: %d: \n%s.\n", pZdanie->poczatek_wiersz,
							pZdanie->koniec_wiersz, pZdanie->iloscWyrazow, pZdanie->iloscInterpunkcyjnych, pZdanie->tekst);
						pZdanie = pZdanie->nastepny;
					}
					fprintf(plik, "\n");
				}
					
			fclose(plik);
		}
	}
}