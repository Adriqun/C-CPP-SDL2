#include <iostream>

long double operator"" _cm(long double x)	{ return x * 10; }
long double operator"" _m(long double x)	{ return x * 1000; }
long double operator"" _mm(long double x)	{ return x; }

int operator"" _strBin2Dec(const char* str, size_t length) {
	int ret = 0;
	for (int i = 0; i < length; ++i) {
		ret = ret << 1;
		if (str[i] == '1')
			ret += 1;
	}
	return ret;
}

int main()
{
	long double height = 3.4_cm;
	std::cout << height + 5.0_m << "\n";
	std::cout << "110"_strBin2Dec;
	return 0;
}