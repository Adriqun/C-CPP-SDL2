#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

class BigArray
{
	vector <int> v; // huge vector
	mutable int accessCounter;	// mutable means if we have const
									// function we can change the value of class
	int* v2; // another int array
	
public:

	int getItem( int index ) const
	{
		accessCounter ++;
		//const_cast <BigArray*>( this )->accessCounter++;
		// cast looks bad
		return v[ index ];
	}
	
	// this is not const function in bitwise constness
	
	void setV2Item( int index, int x )	const
	{
		*( v2+index ) = x;
	}
};

int main(int argc, char **argv)
{
	BigArray b;
	
	return 0;
}
