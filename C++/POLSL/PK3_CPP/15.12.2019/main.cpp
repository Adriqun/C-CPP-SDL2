#include <iostream>
// Bez operatorow iostream

class Tekst
{
	char* napis;
	unsigned int rozmiar;

	void Utworz(const Tekst&);
	unsigned int Dlugosc(char*); // nie uzywamy C, wiec to nasz strlen
	void Kopiuj(char*, const unsigned int*);
	bool Porownaj(char*, const unsigned int*);
	void Dodaj(char*, const unsigned int*);
	Tekst Wytnij(unsigned int, unsigned int);

public:
	Tekst(); // Tworzy pusty tekst
	Tekst(char*); // Kopiuje ciag znakow
	Tekst(const Tekst&);
	~Tekst();

	const Tekst& operator=(const Tekst&);
	bool operator==(const Tekst&);
	Tekst operator+(const Tekst&); // konkatenacja
	Tekst operator()(unsigned int, unsigned int); // zwaraca kopie napisu
	void operator--();
};

void Tekst::Utworz(const Tekst& rhs)
{
	delete[] napis;
	rozmiar = rhs.rozmiar;
	napis = new char[rozmiar];
	for (unsigned int i = 0; i < rozmiar; ++i)
		napis[i] = rhs.napis[i];
}

unsigned int Tekst::Dlugosc(char* wskaznik)
{
	if (!wskaznik)
		return 0;

	unsigned int dlugosc = 1; // 1 bo \0 nie jest liczone
	while (*wskaznik)
	{
		++dlugosc;
		++wskaznik;
	}

	return dlugosc;
}

void Tekst::Kopiuj(char* nowyNapis, const unsigned int* nowaDlugosc)
{
	if (nowyNapis)
	{
		delete[] napis;
		rozmiar = nowaDlugosc ? *nowaDlugosc : Dlugosc(nowyNapis);
		napis = new char[rozmiar];
		char* kopia = napis;
		while (*nowyNapis)
		{
			*kopia = *nowyNapis;
			++kopia, ++nowyNapis;
		}
		*kopia = '\0';
	}
}

bool Tekst::Porownaj(char* innyNapis, const unsigned int* innaDlugosc)
{
	unsigned int drugaDlugosc = innaDlugosc ? *innaDlugosc : Dlugosc(innyNapis);

	if (rozmiar != drugaDlugosc)
		return false;

	char* kopia = napis;
	while (*innyNapis)
	{
		if (*kopia != *innyNapis)
			return false;
		++kopia, ++innyNapis;
	}

	return !*innyNapis;
}

void Tekst::Dodaj(char* innyNapis, const unsigned int* innaDlugosc)
{
	unsigned int drugaDlugosc = innaDlugosc ? *innaDlugosc : Dlugosc(innyNapis);
	unsigned int nowaDlugosc = rozmiar + drugaDlugosc - 1; // -1 bo mamy dwa razy \0
	char* staryNapis = napis;

	napis = new char[nowaDlugosc];

	// Przepisanie starego napisu
	for (unsigned int i = 0; i < rozmiar - 1; ++i)
		napis[i] = staryNapis[i];
	delete[] staryNapis;

	for (unsigned int i = rozmiar - 1; i < nowaDlugosc; ++i)
		napis[i] = innyNapis[i - rozmiar + 1];

	rozmiar = nowaDlugosc;
}

Tekst Tekst::Wytnij(unsigned int start, unsigned int dlugosc)
{	// Dlugosc podajemy wraz z \0

	if (start >= dlugosc)
		return Tekst(); // Zwroc pusty tekst zawierajacy \0

	if (start + dlugosc > rozmiar)
		return Tekst(); // Zwroc pusty tekst zawierajacy \0

	// Zwroc wycinek
	char* wycinek = &napis[start]; // Pozycja pierwszego znaku wycinka

	Tekst nowyTekst;
	nowyTekst.rozmiar = dlugosc;
	delete[] nowyTekst.napis;
	nowyTekst.napis = new char[dlugosc];

	// Kopiowanie wycinka
	char* a = nowyTekst.napis;
	char* b = napis;
	while (*b)
	{
		*a = *b;
		++a, ++b;
	}
	nowyTekst.napis[dlugosc - 1] = '\0';

	// Zwrot
	return nowyTekst;
}

Tekst::Tekst()
{
	napis = nullptr;
	char nowyNapis[1] = "";
	Kopiuj(nowyNapis, nullptr);
}

Tekst::Tekst(char* nowyNapis)
{
	napis = nullptr;
	Kopiuj(nowyNapis, nullptr);
}

Tekst::Tekst(const Tekst& nowyNapis)
{
	napis = nullptr;
	Kopiuj(nowyNapis.napis, &nowyNapis.rozmiar);
}

Tekst::~Tekst()
{
	delete[] napis;
	napis = nullptr;
	rozmiar = 0;
}


const Tekst& Tekst::operator=(const Tekst& nowyNapis)
{
	Kopiuj(nowyNapis.napis, &nowyNapis.rozmiar);
	return *this;
}

bool Tekst::operator==(const Tekst& innyNapis)
{
	return Porownaj(innyNapis.napis, &innyNapis.rozmiar);
}

Tekst Tekst::operator+(const Tekst& innyNapis)
{
	Dodaj(innyNapis.napis, &innyNapis.rozmiar);
	return *this;
}

Tekst Tekst::operator()(unsigned int start, unsigned int dlugosc)
{
	return Wytnij(start, dlugosc);
}

void Tekst::operator--()
{
	if (!*napis)
		return;

	Tekst kopia(this->napis);

	char* prawy = kopia.napis;
	char* lewy = napis;

	unsigned int roz = rozmiar - 2; // pomijamy '\0'
	for (unsigned int i = 0; i <= roz; ++i)
		lewy[i] = prawy[roz - i];
}

int main()
{
	char txt1[] = "Dawid";
	char txt2[] = "Bartosz";
	char txt3[] = "Anastazja";

	Tekst tester1;
	tester1 = txt1;

	Tekst tester2(txt2);

	Tekst tester3;
	tester3 = txt3;
	Tekst tester4(tester3);

	bool wynik = tester3 == tester4;
	tester1 = tester1 + tester2;
	--tester3;
	tester1 = Tekst();

	return 0;
}