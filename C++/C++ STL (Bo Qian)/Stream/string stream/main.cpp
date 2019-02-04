#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
using namespace std;

int main()
{
	stringstream ss;	// stream without IO operation
	// read/write of string
	
	ss << 89 << "  Hex:  " << hex << 89 << "  Oct:  " << oct << 89;
	cout << ss.str() << endl;

	int a, b, c;
	string s1;

	ss >> hex >> a;	// a==137
	ss >> s1;		// s1=="Hex:"
	ss >> dec >> b;	// b==59

	ss.ignore(6);
	ss >> oct >> c;	// c==89

	return 0;
}