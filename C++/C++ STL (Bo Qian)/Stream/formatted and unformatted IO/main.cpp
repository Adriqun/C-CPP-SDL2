#include <iostream>
#include <string>
#include <fstream>

int main()
{
	using namespace std;

	// Formatting
	cout << 34 << endl; // 34
	cout.setf(ios::oct, ios::basefield);
	cout << 34 << endl; // 42
	cout.setf(ios::showbase);
	cout << 34 << endl;	// 042
	cout.setf(ios::hex, ios::basefield);
	cout << 34 << endl;	// 0x22
	
	cout.unsetf(ios::showbase);

	cout.width(10);
	cout << 26 << endl; //           26
	cout.setf(ios::left, ios::adjustfield); // 26


	// Floating point value
	cout.setf(ios::scientific, ios::floatfield);
	cout << 340.1 << endl;	// 3.401000e+02
	cout.setf(ios::fixed, ios::floatfield);
	cout << 340.1 << endl;	// 340.100000
	cout.precision(3);
	cout << 340.1 << endl;	// 340.100

	int i;
	cin.setf(ios::hex, ios::basefield);
	cin >> i;	// Enter: 12
	// i == 18

	ios::fmtflags f = cout.flags();
	cout.flags(ios::oct | ios::showbase);





	// Member functions for unformatted IO

	// INPUT
	ifstream inf("file.txt");
	char buf[80];
	inf.get(buf, 80);		// Read up to 80 chars and save them into buf.
	inf.getline(buf, 80);	// Read up to 80 char or until /n'
	inf.read(buf, 20);		// Read 20 chars.
	inf.ignore(3);			// Ignore next 3 chars in the stream
	inf.peek();				// Ignore char on top of the stream
	inf.unget();			// return a last read character
	inf.get();
	inf.gcount();			// return the number of chars being read by last unformatted read


	// OUTPUT
	ofstream of("file.txt");
	of.put('c');
	of.write(buf, 6);	// write first 6 chars of buf
	of.flush();			// flash the output


	return 0;
}
