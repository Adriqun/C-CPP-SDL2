#include <iostream>
#include <string>
#include <fstream>

int main()
{
	std::ofstream of("file.txt", std::ios::in | std::ios::out);
	of << "Honesty is the best policy";

	of.seekp(10, std::ios::beg);	// Move the output pointer 10 chars after begin
	of << "123";
	of.seekp(-5, std::ios::end);	// Move the output pointer 5 chars before end
	of << "456";
	of.seekp(-6, std::ios::cur);	// Move the output pointer 6 chars before current position
	of << "789";

	std::ifstream ifs("file2.txt");
	int i;
	ifs >> i;

	ifs.good();	// Everything is ok, (goodbit == 1).
	ifs.bad();	// Non-recoverable error (badbit == 1).
	ifs.fail();	// Failed stream operation (failbit == 1, badbit == 1).
	ifs.eof();	// End of file, (eofbit == 1).

	ifs.clear();					// Clear all the error status.
	ifs.clear(std::ios::badbit);	// Clear all the errors status except badbit.

	ifs.rdstate();									// Read the current status flag.
	ifs.clear(ifs.rdstate() & ~std::ios::failbit);	// Clear only failbit.

	// When the badbit or failbit are set to 1, exception of ios::failure will be thrown.
	ifs.exceptions(std::ios::badbit | std::ios::failbit);

	ifs.exceptions(std::ios::goodbit);	// No exceptions.
	return 0;
}
