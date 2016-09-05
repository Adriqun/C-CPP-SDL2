#include <iostream>

using namespace std;

class Box
{
	int w;
	int h;
	
public:
	
	Box()
	{
		w = 0;
		h = 0;
	}
	
	ostream& operator <<( ostream& s )
	{
		return s << "width: " << w << " height: " << h << endl;
	}
	
	istream& operator >>( istream& s )
	{
		return s >> w >> h;
	}
};


int main(int argc, char **argv)
{
    Box box;
	
	box << cout;
	cout << "Write 2 numbers: ";
	box >> cin;
	box << cout;
	
    return 0;
}
