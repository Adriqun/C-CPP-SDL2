#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

int main()
{
	streambuf* pBuf = cout.rdbuf();
	ostream myCout(pBuf);
	myCout << 34; // 34
	myCout.setf(ios::showpos);
	myCout.width(5);
	myCout << 12 << endl;	//      +12
	cout << 12 << endl;	// 12


	ofstream of("file.txt");
	streambuf* origBuf = cout.rdbuf();
	cout.rdbuf(of.rdbuf());
	cout << "Hello" << endl;	// file.txt has "Hello\n"
	cout.rdbuf(origBuf);


	// read then print the input until == 'x'
	istreambuf_iterator<char> i(cin);
	ostreambuf_iterator<char> o(cout);
	while (*i != 'x')
	{
		*o = *i;
		++o;
		++i;
	}

	// same
	// copy(istreambuf_iterator<char>(cin), istreambuf_iterator<char>(), ostreambuf_iterator<char>(cout))


	return 0;
}