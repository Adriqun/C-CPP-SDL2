#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

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
		przerwy = nowa;
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
	// uzupelnij liste
	Uzupelnij();

	// wypisz jak dane wygladaja
	WypiszDni();

	// pobierz dane od uzytkowanika
	int start = 0, end = 0;
	printf("\nPodaj dzien miesiaca od ktorego zaczac liczyc liczbe przepracowanych godzin: \n");
	scanf("%d", &start);
	printf("Podaj dzien miesiaca do ktorego zaczne liczyc liczbe przepracowanych godzin (wlacznie): \n");
	scanf("%d", &end);

	// wypisz sumaryczny czas pracy
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

	// Zakoncz.
	{
		char c = 0;
		printf("Wcisnij enter zeby wyjsc...\n");
		while (c != '\r' && c != '\n')
			c = getchar();
	}

	return 0;
}