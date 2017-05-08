#include <stdio.h>
#include <iostream>

using namespace std;

class Dog
{
	string name;
	int age;
	
public:
	Dog() { age = 3; name = "dummy"; }
	
	// const parameters
	void setAge( const int& a ) { age = a; }
	void setAge( int& a ) { age = a; }
	
	// const return value
	const string& getName() {return name;}
	
	// const function
	void printDogName() const { cout << name << " const" << endl; }
	void printDogName() { cout << getName() << " non-const" << endl; }
};

int main()
{
	Dog d1;
	d1.printDogName();
	
	const Dog d2;
	d2.printDogName();
	
	return 0;
}
