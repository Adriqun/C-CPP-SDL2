#include <iostream>
#include <string>

struct Dog {
	void bark(int age) { std::cout << "I am " << age << " years old." << std::endl; }
	virtual void bark(std::string msg = "just a") { std::cout << "I am " << msg << " dog" << std::endl; }
};

struct YellowDog : public Dog {
	// solution
	using::Dog::bark;
	//
	virtual void bark(std::string msg = "Yellowdog") { std::cout << "I am " << msg << " dog" << std::endl; }
};

int main()
{
	YellowDog* yd = new YellowDog;
	yd->bark();
	yd->bark(2); // problem
	delete yd;
	return 0;
}