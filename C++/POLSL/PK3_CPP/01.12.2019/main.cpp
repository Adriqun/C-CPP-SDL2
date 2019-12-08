#include <iostream>
#include <random>

// Zad 1.
int* Allocate(size_t size)
{
	return new int(size);
}

void Deallocate(int* ptr)
{
	delete[] ptr;
}

void Print(int* ptr, size_t size)
{
	for (size_t i = 0; i < size; ++i)
		std::cout << ptr[i] << ' ';
}

// Zad 2.
template<class T>
void MultiplySum(T &mul, T &sum, const T a, const T b)
{
	mul = a * b;
	sum = a + b;
}

template<class T>
void MultiplySum(T* &mul, T* &sum, const T* a, const T* b, int size)
{
	while (--size) {
		mul[size] = a[size] * b[size];
		sum[size] = a[size] + b[size];

	}

	mul[0] = a[0] * b[0];
	sum[0] = a[0] + b[0];
}

// Zad 3.
class ComplexNumber
{
	float real;
	float imagine;
	static int counter;
	int id;

public:
	ComplexNumber() {
		real = imagine = 0.0;
		id = counter;
		++counter;
	}

	ComplexNumber(float real, float imagine) {
		this->real = real;
		this->imagine = imagine;
		id = counter;
		++counter;
	}

	void Add(ComplexNumber &a)
	{
		this->real += a.real;
		this->imagine += a.imagine;
	}

	void Add(float a)
	{
		this->real += a;
	}

	void Substract(ComplexNumber &a)
	{
		this->real -= a.real;
		this->imagine -= a.imagine;
	}

	void Substract(float &b)
	{
		this->real -= b;
	}

	float Modulo(ComplexNumber x)
	{
		return sqrt(x.real * x.real + x.imagine * x.imagine);
	}

	friend std::ostream& operator <<(std::ostream& os, const ComplexNumber &a)
	{
		os << "Count: " << ComplexNumber::counter << ", Object ID = " << a.id << ", Number: " << a.real << " " << a.imagine << "i \n";
		return os;
	}

	friend std::istream& operator >>(std::istream& is, ComplexNumber& a)
	{
		is >> a.real >> a.imagine;
		return is;
	}
};

int ComplexNumber::counter = 0;

int main()
{
	// Zad 1 - Test
	/*{
		const size_t length = 10;
		int* tab = Allocate(length);
		auto Fill = [&]() {
			std::random_device RD;
			std::mt19937 MT(RD());
			std::uniform_real_distribution<double> distribution(1, length);
			for (int i = 0; i < length; ++i)
				tab[i] = static_cast<int>(distribution(MT));
		};
		Fill();
		Print(tab, length);
		Deallocate(tab);
	}*/

	// Zad 2 - Test
	/*{
		{
			int mul, sum;
			const int a = 12, b = 5;
			MultiplySum(mul, sum, a, b);
		}

		{
			const int length = 3;
			int* a = new int[length];
			int* b = new int[length];
			for (int i = 0; i < length; ++i) {
				a[i] = i;
				b[i] = a[i] + 1;
			}
			delete[] a;
			delete[] b;
		}
	}*/

	// Zad 3 - Test
	{
		const int length = 5;
		ComplexNumber static_cn[length];
		static_cn[2] = static_cn[0] = ComplexNumber(4.0, 5.0);
		std::cout << static_cn[0];
		static_cn[1] = ComplexNumber(3.0, 2.0);
		std::cout << static_cn[1];

		std::cout << "Add:" << std::endl;
		static_cn[0].Add(static_cn[1]);
		std::cout << static_cn[0];

		std::cout << "Substract:" << std::endl;
		static_cn[2].Substract(static_cn[1]);
		std::cout << static_cn[0];

		ComplexNumber* dynamic_cn = new ComplexNumber[length];
		delete[] dynamic_cn;

		ComplexNumber a1, a2(), a3(15.0, 10.0);
		ComplexNumber* b1, * b2, * b3;
		b1 = new ComplexNumber;
		b2 = new ComplexNumber();
		b3 = new ComplexNumber(3.0, 4.0);
		delete b1;
		delete b2;
		delete b3;
	}

	return 0;
}