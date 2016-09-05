#include <iostream>

using namespace std;

class Reactangle
{
	int a;
	int area;
	
public:
	
	Reactangle( int a )
	{
		this->a = a;
	}
	
	int operator *=( int b )
	{
		area = this->a * b;
		return this->a * b;
	}
	
	ostream& operator <<( ostream& s )
	{
		return s << "Area: " << area << endl;
	}
	
};

int main(int argc, char **argv)
{
    Reactangle rect( 5 );
	
	rect << cout;
	
	rect *= 5;
	
	rect << cout;
	
    return 0;
}
