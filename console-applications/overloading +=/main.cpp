#include <iostream>

using namespace std;

class Square
{
	int a;
	int area;
	
public:
	
	Square( int a )
	{
		this->a = a;
		area = a*a;
	}
	
	int operator +=( int area )
	{
		return this->area += area;
	}
	
	int getArea()
	{
		return area;
	}
	
	ostream& operator <<( ostream& s )
	{
		return s << "Area: " << area << endl;
	}
	
};

int main(int argc, char **argv)
{
    Square square( 5 );
	
	square << cout;
	
	square += 25;
	
	square << cout;
	
    return 0;
}
