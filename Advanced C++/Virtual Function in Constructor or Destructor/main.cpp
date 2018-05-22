#include <iostream>

using namespace std;

class Dog
{
public:
	Dog() { cout << "Dog born." << endl; bark(); }
	virtual void bark() { cout << "I am a just a dog" << endl; }
	void seeCat() { bark(); }
	~Dog() { bark(); }
};

class Yellowdog :public Dog
{
public:
	Yellowdog() { cout << "Yellow dog born." << endl; }
	virtual void bark() { cout << "I am yellow dog" << endl; }
};

int main()
{
	Yellowdog d;
	d.seeCat();
	
	return 0;
}
