#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum DzienTygodnia
{
	Pon, Wto, Sro, Czw, Pia, Sob, Nie
};

char* DzienTygodniaStr[7] = { "Poniedzialek", "Wtorek", "Sroda", "Czwartek", "Piatek", "Sobota", "Niedziela" };

typedef struct Czas
{
	int godzina;
	int minuta;
} TCzas;

int CzasWMinutach(TCzas start, TCzas koniec)
{
	if (koniec.godzina < start.godzina)
		return 0;
	if (koniec.godzina == start.godzina)
	{
		if (koniec.minuta < start.minuta)
			return 0;
	}

	int a = koniec.godzina * 60 + koniec.minuta;
	int b = start.godzina * 60 + start.minuta;
	return a - b;
}

TCzas MinutyNaCzas(int minut)
{
	int c = 0;
	while (minut >= 60)
	{
		++c;
		minut -= 60;
	}

	TCzas czas;
	czas.godzina = c;
	czas.minuta = minut;
	return czas;
}

typedef struct Przerwa
{
	TCzas poczatek;
	TCzas koniec;
	struct Przerwa* nastepny;
} TPrzerwa;

typedef struct DzienPracy
{
	int data; // numer dnia miesiaca
	enum DzienTygodnia dzien;
	TCzas poczatek;
	TCzas koniec;
	TPrzerwa* przerwa;
	struct DzienPracy* nastepny;
} TDzienPracy;

TDzienPracy* dnipracy = NULL;

void DodajDzienPracy(enum DzienTygodnia dzien, TCzas poczatek, TCzas koniec, TPrzerwa** przerwy)
{
	if (!dnipracy)
	{	// Pierwszy dzien miesiaca.
		dnipracy = (TDzienPracy*) malloc(sizeof(TDzienPracy));
		dnipracy->data = 1;
		dnipracy->dzien = dzien;
		dnipracy->poczatek = poczatek;
		dnipracy->koniec = koniec;
		dnipracy->przerwa = *przerwy;
		dnipracy->nastepny = NULL;
	}
	else
	{
		TDzienPracy* ptr = dnipracy;
		while (ptr->nastepny)
			ptr = ptr->nastepny;

		// Jestesmy na koncu listy.
		ptr->nastepny = (TDzienPracy*)malloc(sizeof(struct DzienPracy));
		ptr->nastepny->data = ptr->data + 1;
		ptr->nastepny->dzien = dzien;
		ptr->nastepny->poczatek = poczatek;
		ptr->nastepny->koniec = koniec;
		ptr->nastepny->przerwa = *przerwy;
		ptr->nastepny->nastepny = NULL;
	}
}

TPrzerwa* DodajPrzerwe(TCzas poczatek, TCzas koniec)
{
	TPrzerwa* przerwa = (TPrzerwa*) malloc(sizeof(TPrzerwa));
	przerwa->nastepny = NULL;
	przerwa->poczatek = poczatek;
	przerwa->koniec = koniec;
	return przerwa;
}

void DodajPrzerweDoPrzerw(TPrzerwa** przerwy, TPrzerwa* nowa)
{
	if (!przerwy)
	{
		*przerwy = nowa;
		return;
	}

	TPrzerwa* ptr = *przerwy;
	while (ptr->nastepny)
		ptr = ptr->nastepny;
	ptr->nastepny = nowa;
}

TCzas DodajCzas(int godzina, int minuta)
{
	TCzas czas;
	czas.godzina = godzina;
	czas.minuta = minuta;
	return czas;
}

void Wyczysc()
{
	TDzienPracy* ptr = dnipracy;
	while (ptr)
	{
		TDzienPracy* temp = ptr;
		ptr = ptr->nastepny;

		// Wyczysc liste przerw.
		while (temp->przerwa)
		{
			TPrzerwa* przerwa = temp->przerwa;
			temp->przerwa = temp->przerwa->nastepny;
			free(przerwa);
		}

		// Wyczysc Dzien Pracy.
		free(temp);
	}
}

void Uzupelnij()
{
	// 1 dzien miesiaca, poniedzialek
	struct Przerwa* ptrPrzerwa = NULL;
	ptrPrzerwa = DodajPrzerwe(DodajCzas(10, 0), DodajCzas(10, 30));
	DodajPrzerweDoPrzerw(&ptrPrzerwa, DodajPrzerwe(DodajCzas(12, 30), DodajCzas(12, 50)));
	DodajDzienPracy(Pon, DodajCzas(8, 0), DodajCzas(16, 0), &ptrPrzerwa);
	
	// 2 dzien miesiaca, wtorek
	ptrPrzerwa = DodajPrzerwe(DodajCzas(12, 0), DodajCzas(12, 20));
	DodajPrzerweDoPrzerw(&ptrPrzerwa, DodajPrzerwe(DodajCzas(14, 50), DodajCzas(15, 20)));
	DodajDzienPracy(Wto, DodajCzas(9, 30), DodajCzas(17, 30), &ptrPrzerwa);

	// 3 dzien miesiaca, sroda
	ptrPrzerwa = DodajPrzerwe(DodajCzas(10, 0), DodajCzas(10, 50));
	DodajDzienPracy(Sro, DodajCzas(8, 30), DodajCzas(16, 30), &ptrPrzerwa);

	// 4 dzien miesiaca, czwartek
	ptrPrzerwa = DodajPrzerwe(DodajCzas(10, 0), DodajCzas(10, 20));
	DodajPrzerweDoPrzerw(&ptrPrzerwa, DodajPrzerwe(DodajCzas(12, 0), DodajCzas(12, 15)));
	DodajPrzerweDoPrzerw(&ptrPrzerwa, DodajPrzerwe(DodajCzas(14, 0), DodajCzas(14, 15)));
	DodajDzienPracy(Czw, DodajCzas(7, 0), DodajCzas(15, 0), &ptrPrzerwa);

	// 5 dzien miesiaca, piatek
	ptrPrzerwa = DodajPrzerwe(DodajCzas(10, 0), DodajCzas(10, 30));
	DodajPrzerweDoPrzerw(&ptrPrzerwa, DodajPrzerwe(DodajCzas(11, 30), DodajCzas(11, 50)));
	DodajDzienPracy(Pia, DodajCzas(9, 0), DodajCzas(17, 0), &ptrPrzerwa);
}

enum DzienTygodnia DostanDzienTygodnia(const char* str)
{
	if (!strcmp("Pon", str))
		return Pon;
	else if (!strcmp("Wto", str))
		return Wto;
	else if (!strcmp("Sro", str))
		return Sro;
	else if (!strcmp("Czw", str))
		return Czw;
	else if (!strcmp("Pia", str))
		return Pia;
	else if (!strcmp("Sob", str))
		return Sob;
	else if (!strcmp("Sob", str))
		return Sob;
	return Pon;
}

bool BialyZnak(char c)
{
	if (c == '\f' ||
		c == '\r' ||
		c == '\t' ||
		c == '\v' ||
		c == ' ')
		return true;
	return false;
}

TCzas WyciagnijCzasZStringa(const char* str)
{	// Jesli zwroci godzine lub minute = -1 to jest blad.
	TCzas czas;
	czas.godzina = -1;
	czas.minuta = -1;

	bool bMin = false;
	bool bGodz = false;

	int i = 0;
	char* ptr = (char*)str;
	char bufor[2048]; // Bufor na smieci.
	while (ptr)
	{
		if (*ptr == ':')
		{	// Separator.
			bufor[++i] = '\0';
			if (!bMin)
			{
				bMin = true;
				czas.minuta = atoi(bufor);
			}
			else if (bGodz)
			{
				bGodz = true;
				czas.godzina = atoi(bufor);
			}
			else if (bMin || bGodz)
			{
				printf("Blad, format czasu jest nieprawidlowy!\n");
				czas.minuta = -1;
				czas.godzina = -1;
				break;
			}
			i = 0;
		}

		if (*ptr == '-')
		{
			++ptr;
			continue;
		}

		bufor[i] = *ptr;
		++ptr;
	}

	return czas;
}

bool UzupelnijZPliku(const char* nazwapliku)
{
	FILE* plik = NULL;
	plik = fopen(nazwapliku, "r");
	if (!plik)
	{
		printf("Nie mozna otworzyc pliku %s\n", nazwapliku);
		return false;
	}

	// Plik istnieje, wczytujemy.
	int rozmiar;
	char* linia = NULL;
	size_t dlugosc = 0;
	char bufor[2048]; // Bufor na smieci.

	while ((rozmiar = getline(&linia, &dlugosc, plik)) != -1)
	{

		// Dane do dnia pracy.
		int data = -1; // np. 1, 2, 28 itd...
		enum DzienTygodnia dzien; // Pon, Wto, Sro, Czw, Pia, Sob, Nie
		TCzas poczatek;
		TCzas koniec;
		struct Przerwa* ptrPrzerwa = NULL;
		TCzas poczatekPrzerwy;
		TCzas koniecPrzerwy;

		// Pomocne dane.
		bool bData = false, bDzien = false;
		int iPoczatek = 0, iKoniec = 0, iPrzerwa = 0, iLicznikPrzerw = 0;

		int j = 0;
		char znak = ' ';
		for (int i = 0; i < rozmiar; ++i, ++j)
		{
			znak = linia[i];
			if (!BialyZnak(znak))
			{	// Jesli nie jest to separator danych.
				bufor[j] = znak;
			}
			else
			{
				// Jesli jest to bialy znak to sprawdzamy czy nie ma innym bialych znakow.
				// Uzytkownik moze na sile dodac smieci w separatorze ktorych nie chcemy.
				for (; i < rozmiar; ++i)
				{
					if (BialyZnak(linia[i]))
						continue;
					else
						break;
				}

				// Zaznacz koniec danych.
				bufor[++j] = '\0';

				if (!bData)
				{	// Pierwsze zawsze jest data...
					bData = true;
					data = atoi(bufor);
				}
				else if (!bDzien)
				{	// Drugi zawsze jest dzien...
					dzien = DostanDzienTygodnia(bufor);
				}
				else if (iPrzerwa = 1)
				{	// break: wystapilo, przerwy sa ostatnie dlatego maja one wiekszy priorytet.
					++iLicznikPrzerw;
					if (iLicznikPrzerw % 2)
						poczatekPrzerwy = WyciagnijCzasZStringa(bufor);
					else
						koniecPrzerwy = WyciagnijCzasZStringa(bufor);

					if (!ptrPrzerwa)
						ptrPrzerwa = DodajPrzerwe(poczatekPrzerwy, koniecPrzerwy);
					else
						DodajPrzerweDoPrzerw(&ptrPrzerwa, DodajPrzerwe(poczatekPrzerwy, koniecPrzerwy));
				}
				else if (iKoniec == 1)
				{	// end: wystapilo, teraz wczytaj koniec
					++iKoniec;
					koniec = WyciagnijCzasZStringa(bufor);
				}
				else if (iPoczatek == 1)
				{	// pocz: wystapilo, teraz wczytaj poczatek
					poczatek = WyciagnijCzasZStringa(bufor);
					++iPoczatek;
				}
				else if (!strcmp(bufor, "pocz:"))
				{	// Trzeci zawsze jest poczatek.
					if (iPoczatek)
					{
						printf("Blad, nie mozna podac poczatku czasu pracy \"pocz:\" wiecej niz raz!\n");
						fclose(plik);
						return false;
					}
					++iPoczatek;
				}
				else if (!strcmp(bufor, "end:"))
				{	// Czwarty zawsze jest koniec.
					if (iKoniec)
					{
						printf("Blad, nie mozna podac konca czasu pracy \"end:\" wiecej niz raz!\n");
						fclose(plik);
						return false;
					}
					++iKoniec;
				}
				else if (!strcmp(bufor, "break:"))
				{
					if (iPrzerwa)
					{
						printf("Blad, nie mozna podac slowa kluczowego \"break:\" wiecej niz raz!\n");
						fclose(plik);
						return false;
					}
					++iPrzerwa;
				}

				// Reset iteratora.
				j = 0;
			}
		}
	}

	// Zamknij plik.
	fclose(plik);

	// Ok.
	return true;
}

void WypiszDni()
{
	TDzienPracy* ptr = dnipracy;
	while (ptr)
	{
		printf("\n--- Dzien miesiaca: %d, %s ---\n", ptr->data, DzienTygodniaStr[ptr->dzien]);
		printf("Poczatek pracy: %02d:%02d\n", ptr->poczatek.godzina, ptr->poczatek.minuta);
		printf("Koniec pracy: %02d:%02d\n", ptr->koniec.godzina, ptr->koniec.minuta);
		// wypisz przerwy
		printf("Przerwy w pracy: \n");
		if (!ptr->przerwa)
			printf("Brak przerw w pracy!\n");
		else
		{
			TPrzerwa* przerwa = ptr->przerwa;
			while (przerwa)
			{
				printf("  Przerwa: %02d:%02d - %02d:%02d\n", przerwa->poczatek.godzina, przerwa->poczatek.minuta,
					przerwa->koniec.godzina, przerwa->koniec.minuta);
				przerwa = przerwa->nastepny;
			}
		}

		ptr = ptr->nastepny;
	}
}

void WypiszCzasPracy(int start, int end)
{
	TDzienPracy* ptr = dnipracy;
	bool znaleziono_dni = false;
	int suma_minut_pracy = 0;
	int suma_minut_przerwy = 0;
	if (ptr)
	{
		while (ptr)
		{
			if (ptr->data >= start && ptr->data <= end)
			{
				znaleziono_dni = true;
				// Licz minuty pracy.
				suma_minut_pracy += CzasWMinutach(ptr->poczatek, ptr->koniec);

				// Licz minuty przerwy.
				TPrzerwa* przerwa = ptr->przerwa;
				while (przerwa)
				{
					suma_minut_przerwy += CzasWMinutach(przerwa->poczatek, przerwa->koniec);
					przerwa = przerwa->nastepny;
				}
			}

			ptr = ptr->nastepny;
		}
	}

	if (!znaleziono_dni)
		printf("Nie znaleziono godzin pracy w podanym zakresie w miesiacu od %d do %d\n", start, end);
	else
	{
		suma_minut_pracy -= suma_minut_przerwy;
		TCzas czas = MinutyNaCzas(suma_minut_pracy);
		printf("Lacznie %d minut pracy = %d godzin pracy i %d minut pracy\n", suma_minut_pracy, czas.godzina, czas.minuta);
	}
}

int main(int argc, char** argv)
{
	bool status = true;
	if (argc != 1)
	{
		if (argc > 2)
		{
			printf("Maksymalna liczba argumentow to 1\n");
			status = false;
		}
		else
		{	// Jest ok, wczytaj dane z pliku.
			status = UzupelnijZPliku(argv[1]);
		}
	}
	else
	{	// Uzupelnij liste przykladowymi danymi.
		printf("Brak argumentow, uzupelnianie listy przykladowymi danymi...\n");
		Uzupelnij();
	}

	// Wypisz jak dane wygladaja.
	if (status)
	{
		WypiszDni();

		// Pobierz dane od uzytkownika.
		int start = 0, end = 0;
		printf("\nPodaj dzien miesiaca od ktorego zaczac liczyc liczbe przepracowanych godzin: \n");
		scanf("%d", &start);
		printf("Podaj dzien miesiaca do ktorego zaczne liczyc liczbe przepracowanych godzin (wlacznie): \n");
		scanf("%d", &end);

		// Wypisz sumaryczny czas pracy.
		if (start, end)
		{
			if (start > end)
				printf("Zly zakres dni %d-%d\n", start, end);
			else
				WypiszCzasPracy(start, end);
		}


		// wyczysc dane
		Wyczysc();

		{	// Przechwyc \n
			char c = 0;
			while (c != '\r' && c != '\n')
				c = getchar();
		}
	}

	// Zakoncz.
	{
		char c = 0;
		printf("Wcisnij enter zeby wyjsc...\n");
		while (c != '\r' && c != '\n')
			c = getchar();
	}

	return 0;
}