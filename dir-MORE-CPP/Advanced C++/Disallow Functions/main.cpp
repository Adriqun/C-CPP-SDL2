/*
 * 	1. C++ 11: f() = delete;
 * 	2. C++ 03: Declare the function to be private, and not define it.
 * 	3. Private destructor: stay out of stack.
*/


#include <stdio.h>
#include <iostream>

using namespace std;

class OpenFile
{
public:
	
	OpenFile( string filename ) { cout << "Open a file " << filename << endl; }
	void destroyMe() { delete this; }
	
private:
	~OpenFile() { cout <<"OpenFile destructed." << endl; }
};

int main(int argc, char **argv)
{
	OpenFile* of = new OpenFile( "name" );
	of->destroyMe();
	
	return 0;
}
