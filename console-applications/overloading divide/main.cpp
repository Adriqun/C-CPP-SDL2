#include <iostream>

using namespace std;

class Number
{
	int a;
	
public:
	
	Number( int a )
	{
		this->a = a;
	}
	
	int operator /=( int b )
	{
		a /= b;
		return a;
	}
	
	ostream& operator <<( ostream& s )
	{
		return s << "Number: " << a << endl;
	}
	
};

int main(int argc, char **argv)
{
    Number num( 5 );
	
	num << cout;
	
	num /= 5;
	
	num << cout;
	
    return 0;
}
