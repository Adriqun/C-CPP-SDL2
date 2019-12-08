#include <assert.h>
#include <iostream>

class Zbior
{
	const int rozmiar = 100;
	int** tablica;

public:
	Zbior();
	Zbior(const Zbior&);
	Zbior(const Zbior&&);
	~Zbior();
	Zbior& operator =(const Zbior&);
	bool dodaj(int);
	bool usun(int);
	void wyczysc();
	bool nalezy(int);
	void dodajZbior(const Zbior&);
	void wypisz(); // dla testu
};

Zbior::Zbior()
{
	tablica = new int*[rozmiar];
	for (int i = 0; i < rozmiar; ++i)
		tablica[i] = nullptr;
}

Zbior::Zbior(const Zbior& rhs)
{
	tablica = new int* [rozmiar];
	for (int i = 0; i < rozmiar; ++i)
	{
		if (rhs.tablica[i])
		{
			tablica[i] = new int;
			*tablica[i] = *rhs.tablica[i];
		}
		else
			tablica[i] = nullptr;
	}
}

Zbior::Zbior(const Zbior&& rhs)
{
	tablica = new int* [rozmiar];
	for (int i = 0; i < rozmiar; ++i)
	{
		if (rhs.tablica[i])
		{
			tablica[i] = new int;
			*tablica[i] = *rhs.tablica[i];
		}
		else
			tablica[i] = nullptr;
	}
}

Zbior::~Zbior()
{
	wyczysc();
	delete[] tablica;
}

Zbior& Zbior::operator =(const Zbior& rhs)
{
	if (this == &rhs)
		return *this;
	wyczysc();
	for (int i = 0; i < rozmiar; ++i)
		if (rhs.tablica[i])
		{
			tablica[i] = new int;
			*tablica[i] = *rhs.tablica[i];
		}

	return *this;
}

bool Zbior::dodaj(int x)
{
	int fw = rozmiar;
	bool fb = false;
	for (int i = 0; i < rozmiar; ++i)
	{
		if (tablica[i])
		{
			if (*tablica[i] == x)
				return false;
		}
		else if (!fb)
		{
			fb = true;
			fw = i;
		}
	}

	if (fw >= rozmiar)
		return false; // brak miejsca
		
	tablica[fw] = new int;
	*tablica[fw] = x;
	return true;
}

bool Zbior::usun(int x)
{
	for (int i = 0; i < rozmiar; ++i)
	{
		if (tablica[i] && *tablica[i] == x)
		{
			delete tablica[i];
			tablica[i] = nullptr;
			return true;
		}
	}

	return false;
}

void Zbior::wyczysc()
{
	for (int i = 0; i < rozmiar; ++i)
	{
		delete tablica[i];
		tablica[i] = nullptr;
	}
}

bool Zbior::nalezy(int x)
{
	for (int i = 0; i < rozmiar; ++i)
	{
		if (tablica[i] && *tablica[i] == x)
			return true;
	}

	return false;
}

void Zbior::dodajZbior(const Zbior& rhs)
{
	for (int i = 0; i < rozmiar; ++i)
		if (rhs.tablica[i])
			dodaj(*rhs.tablica[i]);
}

void Zbior::wypisz()
{
	for (int i = 0; i < rozmiar; ++i)
		if (tablica[i])
			std::cout << *tablica[i] << " ";
	std::cout << std::endl;
}

int main()
{
	{	// Test 1
		Zbior zbior;
		// Dodawanie
		zbior.dodaj(1);
		zbior.dodaj(2);
		zbior.dodaj(3);
		zbior.dodaj(4);
		assert(!zbior.dodaj(1)); // Powinno dac false
		assert(zbior.nalezy(3));
		assert(zbior.nalezy(4));
		assert(!zbior.nalezy(5));

		std::cout << "1. ";
		zbior.wypisz();

		// Usuwanie
		zbior.usun(3);
		zbior.usun(4);
		assert(!zbior.usun(3)); // Powinno dac false
		assert(!zbior.nalezy(3));
		assert(!zbior.nalezy(4));

		std::cout << "2. ";
		zbior.wypisz();

		// Wyczysc
		assert(zbior.nalezy(1));
		assert(zbior.nalezy(2));
		zbior.wyczysc();
		assert(!zbior.nalezy(1));
		assert(!zbior.nalezy(2));

		std::cout << "3. ";
		zbior.wypisz();
	}

	{	// Test 2
		Zbior a;
		a.dodaj(1);
		a.dodaj(2);
		a.dodaj(3);
		Zbior b(a);
		assert(b.nalezy(1));
		assert(b.nalezy(2));
		assert(b.nalezy(3));

		std::cout << "4. A: ";
		a.wypisz();
		std::cout << "5. B: ";
		b.wypisz();

		Zbior c, d;
		d.dodaj(4);
		d.dodaj(5);
		d.dodaj(6);
		c = d;
		assert(c.nalezy(4));
		assert(c.nalezy(5));
		assert(c.nalezy(6));

		std::cout << "4. C: ";
		c.wypisz();
		std::cout << "5. D: ";
		d.wypisz();

		c = c;
	}

	{	// Test 3
		Zbior a;
		a.dodaj(1);
		a.dodaj(3);
		a.dodaj(4);
		std::cout << "6. A: ";
		a.wypisz();

		Zbior b;
		b.dodaj(3);
		b.dodaj(4);
		b.dodaj(5);

		a.dodajZbior(b);
		std::cout << "7. A: ";
		a.wypisz();


		b.dodaj(8);
		std::cout << "8. B: ";
		b.wypisz();
	}

	return 0;
}