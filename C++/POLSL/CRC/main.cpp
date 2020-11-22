// Autor: Adrian Michalek
// Laboratorium: Technologie Sieciowe TS_NSI
// Prowadzacy: Damian Kusnik
// Temat: L8. Methods of control of transmission correctness
// Data oddania: 22.11.2020

/* compute crc's */
/* crc-ccitt is based on the polynomial x^16+x^12+x^5+1 */
/* The prescription for determining the mask to use for a given polynomial
	is as follows:
		1.  Represent the polynomial by a 17-bit number
		2.  Assume that the most and least significant bits are 1
		3.  Place the right 16 bits into an integer
	Celem Cwiczenia jest modyfikacja kodu, aby liczyl prawidlowo sume CRC dla wielomianu
	CRC64:
	x^{{64}}+x^{{62}}+x^{{57}}+x^{{55}}+x^{{54}}+x^{{53}}+x^{{52}}+
	x^{{47}}+x^{{46}}+x^{{45}}+x^{{40}}+x^{{39}}+x^{{38}}+x^{{37}}+x^{{35}}+x^{{33}}+ x^{{32}}+
	x^{{31}}+x^{{29}}+x^{{27}}+x^{{24}}+x^{{23}}+x^{{22}}+x^{{21}}+x^{{19}}+x^{{17}}+
	x^{{13}}+x^{{12}}+x^{{10}}+x^{9}+x^{7}+x^{4}+x+1
	CRC64: 1010000101111000011100001111010111010100111101010011011010010011
	CRC64:
	64		1 <- ten bit nie jest uwzgledniony w MTT (ok!)
	63-48	0100001011110000
	47-32	1110000111101011
	31-16	1010100111101010
	15-0	0011011010010011
	MTT = 0x42F0E1EBA9EA3693
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MTT 0x42F0E1EBA9EA3693 // Polynomial, crc-ccitt mask

// Update crc
// Wyniki byly porownywane z tymi z strony http://www.sunshine2k.de/coding/javascript/crc/crc_js.html
unsigned long long updcrc_64bit(unsigned long long crc, unsigned char byte, unsigned long long polynomial)
{
	// Funkcja obsluguje 1 bajt na dany moment
	// crc - posrednia wartosc CRC, bedzie to nasz wynik - suma kontrolna (po wykonaniu obliczen na wszystkich bajtach)
	// polynomial - wielomian, dzielnik (staly)
	// CRC64 uzywa wielomianu 65 bitowego, jednak najbardziej znaczacy bit (MSB) jest zawsze = 1 i moze byc "pominiety"
	// stad wielomian i wartosc CRC sa reprezentowane przez liczby 64 bitowe.

	// Za pomoca ponizszych operacji dostajemy aktualna dzielna
	{
		// Zamieniamy 8 bitowego bajta na 64 bitowa wersje (trzeba to zrobic zeby bity mogly sie poprawnie nakryc)
		// byte to jakas wartosc 1 bajtowa = 0xYY
		unsigned long long ebyte = byte; // ebyte = 0x00000000000000YY
		ebyte = ebyte << 56; // Przesuwamy o 56 bitow w lewo, ebyte = 0xYY00000000000000

		crc = crc ^ ebyte; // Na bajcie wykonujemy XOR z aktualna wartoscia posrednia CRC
						   // Poczatkowo crc bedzie = 0, wtedy crc = ebyte (i ten XOR niewiele tu zmienia)
						   // W przeciwnym razie jesli jest to nty bajt to nasza wartosc posrednia crc zawiera reszte
						   // Wtedy ten XOR ma znaczenie. Oba przypadki dadza nam dzielna.
	}

	// Ponizej wyliczamy reszte z dzielenia XOR (czyli teoretycznie dzielna / dzielnik)
	// Algorytm mozna ulepszyc dodajac lookup table, wtedy nie wyliczamy na kazdym bajcie (wywolaniu tej funkcji) reszty
	// tylko mamy juz wczesniej policzone reszty i naszym indexem jest dzielna.
	{
		for (int i = 0; i < 8; i++)
		{
			// 0x8000000000000000 - 64 bitowa wartosc z MSB = 1
			if ((crc & 0x8000000000000000) != 0) // Tu sprawdzamy czy MSB = 1
				crc = (crc << 1) ^ polynomial; // Tak jak w algorytmie, jesli MSB = 1 to wykonujemy XOR z wielomianem
			else
				crc = crc << 1; // Jesli MSB = 0, to przesuwamy
		}
	}

	// Zwracamy "posrednia" wartosc CRC, po wykonaniu obliczen na tym bajcie
	// Po wykonaniu obliczen na wszystkich bajtach, bedzie to suma kontrolna
	return crc;
}

// Wersja 32 bitowa
//unsigned long updcrc_32bit(unsigned long crc, unsigned char byte, unsigned long polynomial)
//{
//	crc ^= (unsigned long)(byte << 24);
//	for (int i = 0; i < 8; i++)
//	{
//		if ((crc & 0x80000000) != 0)
//			crc = (unsigned long)(crc << 1) ^ polynomial;
//		else
//			crc <<= 1;
//	}
//
//	return crc;
//}

// Funkcja do wygenerowania 64 bitowej wartosci wejsciowej
void GenerateExampleDataFile()
{
	unsigned long long data = 0xABCDEF0123456789; // test.bin powinien zawierac hexa "8967452301efcdab"
	FILE* file = fopen("test.bin", "wb");
	fwrite(&data, 8, 1, file);
	fclose(file);

	// Dla Polynomial rownego = 0x42F0E1EBA9EA3693
	// oraz danych wejsciowych = 8967452301efcdab
	// program powinien zwrocic = 0x560996FACC43F7D2
}

// Driver
int main(int argc, char** argv)
{
	GenerateExampleDataFile();

	if (sizeof(MTT) != sizeof(unsigned long long))
	{	// Oczekujemy ze nasz dzielnik - wielomian powinien byc 64 bitowy
		printf("Polynomial should be a 64bit value!\n");
		exit(1);
	}

	if (argc > 2) // Nie pozwalamy aby uzytkownik podal wiecej niz jeden argument
	{
		printf("Usage: ccitt <filename>\n");
		printf("File should contain 64bit value!\n");
		exit(1);
	}

	char filename[2048]; // Bufor do przechowania nazwy pliku
	if (argc == 2)
	{
		// Uzytkownik podal jeden argument
		strcpy(filename, argv[1]);
	}
	else
	{
		// Uzytkownik nie podal argumentow
		printf("Enter filename: ");
		gets(filename);
	}

	FILE* file = fopen(filename, "rb"); // Otwieramy w trybie odczytu plik binarny
	if (!file)
	{	// fopen zwrocil nulla, wypisujemy ze nie mozemy otworzyc pliku
		printf("\nCan't open file");
		exit(1);
	}

	unsigned readNumberOfBytes = 0; // Ilosc odczytanych bajtow
	unsigned long long result = 0; // CRCTT - nasz wynik, suma kontrolna, inicjujemy zerem

	// Zmienne do mierzenia czasu wykonania
	clock_t end, start = clock();

	int ch; // 32 bitowa zmienna byte, oczywiscie powinna wystarczyc 8 bitowa ale zostawiamy bo fgetc zwraca inta
	while ((ch = fgetc(file)) != EOF)
	{
		++readNumberOfBytes; // Zwiekszamy ilosc przeczytanych bajtow
		result = updcrc_64bit(result, ch, MTT);
	}
	end = clock(); // Konczymy mierzyc czas
	fclose(file); // Zamykamy plik

	if (readNumberOfBytes != 8)
	{	// Plik powinien zawierac 8 bajtow, rzucamy bledem
		printf("\nError: Read number of bytes is different than 8, please restart the program and specify file with 64bit value!\n");
		exit(1);
	}

	// Wypisujemy do konsoli liczbe przeczytanych bajtow, wynik oraz czas wykonania
	printf("\nNumber of bytes read from file = %lu\nCRCTT = %llX\n", readNumberOfBytes, result);
	printf("Execution time: %f\n", (float)(end - start) / CLOCKS_PER_SEC);
	return 0;
}