
class Figura3D
{
public:
	virtual ~Figura3D() {}
	virtual double DostanObjetosc() = 0;
	virtual double DostanPolePowierzchni() = 0;
	virtual double DostanStosunekPolaDoObjetosci()
	{
		return DostanPolePowierzchni() / DostanObjetosc();
	}
};

class Kula : public Figura3D
{
	double promien;

public:
	Kula(double promien) : promien(promien) {}
	double DostanObjetosc()
	{
		return 4 / 3 * 3.14 * promien * promien * promien;
	}

	double DostanPolePowierzchni()
	{
		return 4 * 3.14 * promien * promien;
	}

	double DostanStosunekPolaDoObjetosci()
	{
		return DostanPolePowierzchni() / DostanObjetosc();
	}
};

class Prostopadloscian : public Figura3D
{
	double szerokosc;
	double dlugosc;
	double wysokosc;

public:
	Prostopadloscian(double szerokosc, double dlugosc, double wysokosc)
	{
		this->szerokosc = szerokosc;
		this->dlugosc = dlugosc;
		this->wysokosc = wysokosc;
	}

	double DostanObjetosc()
	{
		return szerokosc * dlugosc * wysokosc;
	}

	double DostanPolePowierzchni()
	{
		return	(szerokosc * dlugosc) * 2 +
			(szerokosc * wysokosc) * 2 +
			(dlugosc * wysokosc);
	}

	double DostanStosunekPolaDoObjetosci()
	{
		return DostanPolePowierzchni() / DostanObjetosc();
	}
};

class Walec : public Figura3D
{
	double promien;
	double wysokosc;

public:
	Walec(double promien, double wysokosc)
	{
		this->promien = promien;
		this->wysokosc = wysokosc;
	}

	double DostanObjetosc()
	{
		return 3.14 * promien * promien * wysokosc;
	}

	double DostanPolePowierzchni()
	{
		return 2 * 3.14 * promien * wysokosc;
	}
};

int main()
{
	Figura3D* f1 = new Kula(5);
	Figura3D* f2 = new Prostopadloscian(2, 3, 4);
	Figura3D* f3 = new Walec(5, 4);

	delete f1;
	delete f2;
	delete f3;
	return 0;
}