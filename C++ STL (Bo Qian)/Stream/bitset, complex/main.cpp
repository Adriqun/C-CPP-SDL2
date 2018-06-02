#include <iostream>
#include <string>
#include <fstream>
#include <bitset>
#include <complex>

int main()
{
	std::ofstream of("file.txt");

	of << std::bitset<8>(14) << std::endl; // 00001110
	of << std::complex<int>(2, 3) << std::endl; // (2, 3)

	return 0;
}
