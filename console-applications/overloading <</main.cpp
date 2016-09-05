#include <iostream>

using namespace std;

class Box
{
	int width;
	int height;

public:
	
	Box()
	{
		width = 250;
		height = 250;
	}

	ostream& operator <<( ostream& s )
	{
		return s << width << " " << height << endl;
	}
};


int main(int argc, char **argv)
{
	Box box1;
	
    box1 << cout;
	
    return 0;
}
