#include <iostream>
#include <memory>

using namespace std;

class Dog
{
public:
	
	~Dog()
	{
		cout << "Dog destroyed.\n";
	}
	
	virtual void bark()
	{
		cout << "bark...\n";
	}
};

class Yellowdog: public Dog
{
public:
	~Yellowdog()
	{
		cout << "Yellow dog destroyed.\n";
	}
};

class DogFactory
{
public:
	static shared_ptr <Dog> createYellowDog()
	{
		return shared_ptr <Yellowdog> (new Yellowdog() );
	}
};

class Example
{
public:
	
	~Example()
	{
		cout << "Example destroyed.\n";
	}
};

int main(int argc, char **argv)
{
	shared_ptr <Dog> pd = DogFactory::createYellowDog();
	//... Do something with pd
	
	// delete pd
	
	pd->bark();
	
	Example* example = new Example;
	delete example;
	
	return 0;
}
