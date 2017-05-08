#include <stdio.h>
#include <iostream>
using namespace std;

	// const
	// -A compile time constraint that an object can no be modified
	
void modA( int *x )
{
	*x = 7;
}

int main()
{
	const int a = 3; // I promisse i won't change a
	int *ptr;
	ptr = const_cast<int*>( &a );

	cout << "A=" << a << endl;
	*ptr = 5; // I'm a liar, a is now 5
	cout << "A=" << a << endl;
	
	//const int *p1 = &i // data is const, pointer is not
	//p1++;
	
	//int* const p2;	// pointer is const, data is not
	
	//const int* const p3; // data and pointer are const
	
	
	// Guess
	//int const *p4 = &i;
	
	// If const is on the left of *, data is const
	// If const is on the right of *, pointer is const
	
	
	
	return 0;
}
