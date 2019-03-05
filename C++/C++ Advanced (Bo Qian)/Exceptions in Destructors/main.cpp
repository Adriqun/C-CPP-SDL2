#include <stdio.h>
#include <iostream>

using namespace std;

class Dog
{
	
public:

	string m_name;
	
	Dog( string name )
	{
		m_name = name; cout << name << " is born." << endl;
	}
	
	~Dog()
	{
		cout << m_name << " is destroyed.\n";
	}
	
	void prepareToDestr() { /*...;*/ throw m_name; }
	void bark() { /*...*/ }
};

int main()
{
	try
	{
		Dog dog1( "Henry" );
		Dog dog2( "Bob" );
		
		dog1.bark();
		dog2.bark();
		
		dog1.prepareToDestr();
		dog2.prepareToDestr();
	}
	catch()
	{
		cout << msg << " is caught" << endl;
	}
	
	return 0;
}
