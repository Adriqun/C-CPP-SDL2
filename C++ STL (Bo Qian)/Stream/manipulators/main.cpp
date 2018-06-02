#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// that's how the endl function looks like
ostream& endl(ostream& sm)
{
	sm.put('\n');
	sm.flush();
	return sm;
}

// << operator
ostream& ostream::operator<<(ostream& (*func)(ostream&))
{
	return (*func)(*this);
}

int main()
{
	cout << ends;	// '\0'
	cout << flush;
	cin >> ws;	// read and discard white spaces

	cout << setw(8) << left << setfill('_') << 99 << endl;	// 99______

	cout << hex << showbase << 14;	// 0xe

	return 0;
}
