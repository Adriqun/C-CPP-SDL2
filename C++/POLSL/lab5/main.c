#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

typedef struct Wezel
{
	unsigned char* pSlowo;
	int nRazy; // jak wiele razy slowo wystapilo
	struct Wezel* nastepny;
} Wezel;

#define MAX_WORD_LENGTH 2048
int iStat[MAX_WORD_LENGTH];
Wezel* pGlowy[MAX_WORD_LENGTH];

void wyczysc()
{
	for (int i = 0; i < MAX_WORD_LENGTH; ++i)
	{
		if (pGlowy[i])
		{
			Wezel* ptrWezel = pGlowy[i];
			while (ptrWezel)
			{
				Wezel* delWezel = ptrWezel;
				ptrWezel = ptrWezel->nastepny;
				free(delWezel->pSlowo);
				free(delWezel);
			}
			pGlowy[i] = NULL;
		}
	}
}

bool jestZerowy(char c)
{	// zgodnie z trescia zadania jest bezsensu, dlatego dodalem kilka dodatkowych znakow
	if (c == '\n' || c == ' ' || c == ',' || c == '.' || c == ';' || c == ':' || c == '(' || c == ')')
		return true;
	return false;
}

int main(int argc, char** argv)
{
	// switche
	bool bPlik = false; // r <nazwa pliku>
	bool bStatystyka = false; // s - utworz statystyke wyrazow i wydrukuj na konsole
	bool bWydrukujKons = false; // p <liczba> - wydrukuj na konsole n najdluzszych wyrazow
	bool bZapiszDoPliku = false; // w <nazwa pliku> - zapisz raport do pliku
	bool bZakoncz = false; // q - zakoncz dzialanie programu

	char c = 0;
	bool bylPlik = false;
	bool wyswietlRaz = false;
	bool wyswietlInfo = true;
	while (true)
	{
		// wypisz mozliwosci i pobierz znak
		if (!wyswietlRaz)
		{
			wyswietlRaz = true;
			printf("Podaj opcje programu, dostepne opcje:\n");
			printf("r <nazwa pliku> - wczytuje zadany plik\n");
			printf("s - utworz statystyke wyrazow i wydrukuj na konsole\n");
			printf("p <liczba> - wydrukuj na konsole <liczba> najdluzszych wyrazow\n");
			printf("w <nazwa pliku> - zapisz raport do pliku\n");
			printf("q - zakoncz dzialanie programu\n");
		}
		else if (wyswietlInfo)
			printf("Podaj opcje programu: ");
		wyswietlInfo = false;
		c = getchar();

		{	// Zabezpieczenie przed nowymi liniami
			char prev = c;
			while (c != '\r' && c != '\n')
				c = getchar();
			c = prev;
		}

		switch (c)
		{
			case 'r': bPlik = true; break;
			case 's': bStatystyka = true; break;
			case 'p': bWydrukujKons = true; break;
			case 'w': bZapiszDoPliku = true; break;
			case 'q': bZakoncz = true; break;
		}

		// przywilej bycia pierwszym
		if (bZakoncz)
			break;

		if (bPlik)
		{
			bPlik = false;
			wyswietlInfo = true;
			if (bylPlik)
			{	// jesli byl plik to wszystkie wczesniejsze zebrane info kasujemy
				wyczysc();
				bylPlik = false;
			}

			// zaznaczamy ze przy podaniu pliku zamykamy go w tej samej iteracji
			printf("Podaj nazwe pliku: ");
			char cBufor[MAX_WORD_LENGTH];
			scanf("%s", cBufor);

			// otwieramy plik
			FILE* pPlik = fopen(cBufor, "r"); // read only
			if (!pPlik)
			{
				printf("Nie mozna otworzyc podanego pliku %s\n", cBufor);
				continue;
			}

			// probujemy wczytac z pliku
			unsigned char ch;
			int iLen = 0;
			while (ch = fgetc(pPlik))
			{
				//if (ch < -1 || ch > 127)
					//continue; // pomin nie ASCII
				if (!jestZerowy(ch))
				{
					cBufor[iLen] = ch;
					++iLen;
					if (iLen >= MAX_WORD_LENGTH)
					{	// undefinied behaviour
						printf("Blad: maksymalna dlugosc slowa to %d\n", MAX_WORD_LENGTH);
						fclose(pPlik);
						break;
					}
				}
				else
				{	// dodaj do listy
					char* pTemp = (char*)malloc(iLen + 1);
					for (int i = 0; i < iLen; ++i)
						pTemp[i] = cBufor[i];
					pTemp[iLen] = '\0';
					++iStat[iLen];

					Wezel** pWezel = &pGlowy[iLen];
					// przeszukaj
					while (*pWezel)
					{
						if ((*pWezel)->pSlowo && !strcmp(pTemp, (*pWezel)->pSlowo))
							break;
						pWezel = &(*pWezel)->nastepny;
					}

					iLen = 0;
					if (*pWezel)
					{
						++(*pWezel)->nRazy;
						free(pTemp);
					}
					else
					{	// koniec listy, czyli slowa nie znaleziono
						*pWezel = malloc(sizeof(Wezel));
						(*pWezel)->pSlowo = pTemp;
						(*pWezel)->nRazy = 1;
						(*pWezel)->nastepny = NULL;
					}
				}

				if (/*ch == EOF*/ch == 0xFF) // koniec lini dla unsigned
					break;
			}

			// zamknij plik
			fclose(pPlik);
			bylPlik = true;
		}
		else if (bStatystyka)
		{
			bStatystyka = false;
			wyswietlInfo = true;
			if (!bylPlik)
				printf("Nalezy najpierw wczytac plik w celu zebrania informacji!\n");
			else
			{
				int maxSlIlosc = 0;
				// zaczynamy szukac czy sa gdzies wyrazy o danej dlugosci i jest ich <ilosc>
				// najpierw wyznaczamy najwieksza ilosc danej dlugosci wyrazow
				for (unsigned i = 0; i < MAX_WORD_LENGTH; ++i)
				{
					if (maxSlIlosc < iStat[i])
						maxSlIlosc = iStat[i];
				}

				if (!maxSlIlosc)
				{
					printf("Nie znaleziono zadnych slow\n");
					continue;
				}

				while (maxSlIlosc > 0)
				{
					for (unsigned i = 0; i < MAX_WORD_LENGTH; ++i)
					{
						if (iStat[i] == maxSlIlosc)
							printf("Znaleziono %d wyrazow o dlugosci %d\n", iStat[i], i);
					}

					// zmniejsz
					--maxSlIlosc;
				}
			}
		}
		else if (bWydrukujKons)
		{
			bWydrukujKons = false;
			wyswietlInfo = true;
			if (!bylPlik)
				printf("Nalezy najpierw wczytac plik w celu zebrania informacji!\n");
			else
			{
				int n, m;
				printf("Podaj <liczbe>: ");
				scanf("%d", &n);
				m = n;
				int i = MAX_WORD_LENGTH;
				// lecimy od konca
				while (--i)
				{
					if (n <= 0)
						break;

					if (pGlowy[i])
					{
						Wezel* ptr = pGlowy[i];
						while (ptr)
						{
							--n;
							printf("%s\n", ptr->pSlowo);
							ptr = ptr->nastepny;
						}
					}
				}

				if (n == m)
					printf("Nie znaleziono zadnych wyrazow\n");
			}
		}
		else if (bZapiszDoPliku)
		{
			bZapiszDoPliku = false;
			wyswietlInfo = true;
			if (!bylPlik)
				printf("Nalezy najpierw wczytac plik w celu zebrania informacji!\n");
			else
			{
				// zaznaczamy ze przy podaniu pliku zamykamy go w tej samej iteracji
				printf("Podaj nazwe pliku do ktorego przekierowac statystyke: ");
				char cBufor[MAX_WORD_LENGTH];
				scanf("%s", cBufor);

				// otwieramy plik
				FILE* pPlik = fopen(cBufor, "w+"); // write only
				if (!pPlik)
				{
					printf("Nie mozna otworzyc podanego pliku %s\n", cBufor);
					continue;
				}

				int maxSlIlosc = 0;
				// zaczynamy szukac czy sa gdzies wyrazy o danej dlugosci i jest ich <ilosc>
				// najpierw wyznaczamy najwieksza ilosc danej dlugosci wyrazow
				for (unsigned i = 0; i < MAX_WORD_LENGTH; ++i)
				{
					if (maxSlIlosc < iStat[i])
						maxSlIlosc = iStat[i];
				}

				if (!maxSlIlosc)
				{
					fprintf(pPlik, "Nie znaleziono zadnych slow\n");
					continue;
				}

				while (maxSlIlosc > 0)
				{
					for (unsigned i = 0; i < MAX_WORD_LENGTH; ++i)
					{
						if (iStat[i] == maxSlIlosc)
							fprintf(pPlik, "Znaleziono %d wyrazow o dlugosci %d\n", iStat[i], i);
					}

					// zmniejsz
					--maxSlIlosc;
				}

				fclose(pPlik);
			}
		}
	}

	if (bylPlik)
		wyczysc();
	return 0;
}
