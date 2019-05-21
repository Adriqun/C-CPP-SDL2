#include "kontener.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
	Kontener kontener;
	przygotujKontener(&kontener);
	if (sprawdzArgumenty(argc, &argv, &kontener))
	{
		if (sprawdzPlik(&kontener))
		{
			wykonaj(&kontener);
		}	
	}
		

	// wyczysc wszystko
	for (int i = 0; i < MAKSYMALNA_DLUGOSC_ZDANIA; ++i)
	{
		if (kontener.zdania[i])
		{
			Zdanie* pZdanie = kontener.zdania[i];
			while (pZdanie)
			{
				Zdanie* usunZdanie = pZdanie;
				pZdanie = pZdanie->nastepny;
				free(usunZdanie->tekst);
				free(usunZdanie);
			}
		}
	}

	if (kontener.wejscie)
		free(kontener.wejscie);

	if (kontener.wyjscie)
		free(kontener.wyjscie);
	return 0;
}
