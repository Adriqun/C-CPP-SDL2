// author: Adrian Michałek
// email: devmichalek@gmail.com

// const
// A compile time constraint that an object can no be modified

// 1.1 What is the output of the following code?
#include <iostream>

void func(int* x)
{
	*x = 7;
}

int main()
{
	const int a = 3;
	int* ptr;
	ptr = const_cast<int*>(&a);
	std::cout << "A=" << a << std::endl;
	*ptr = 5;
	std::cout << "A=" << a << std::endl;
	*((int*)(&a)) = 6;
	std::cout << "A=" << a << std::endl;
	func((int*)(&a));
	std::cout << "A=" << a << std::endl;
	return 0;
}

// 1.2 Add comments next to p1, p2, p3 and p4, what is const in each line?
//	   Describe "const" with pointers and objects.
int main()
{
	int i;
	const int* p1 = &i;			// comment here
	p1++;
	int* const p2 = &i;			// comment here
	const int* const p3 = &i;	// comment here
	int const* p4 = &i;			// comment here
}

// 1.3 What is the output (and why) of the following code?
#include <iostream>

int main()
{
	int i = 2;
	const int& ref = i;
	const int* ptr = &i;

	i = 2;
	const_cast<int&>(ref) = 3;
	*const_cast<int*>(ptr) = 4;

	std::cout << i << ' ' << ref << ' ' << *ptr;
}

// 1.4 The code below wouldn't compile. Give at least two correct implementations.
// 	   What is the output (and why) of the following code?
//	   You can add or delete only one word in each solution.
#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;

class Dog
{
	string name;
public:
	Dog() { name = "dummy"; printDogName(); }
	const string& getName() { return name; }

	void printDogName() const { cout << getName() << " const" << endl; }
	void printDogName() { cout << getName() << " not const" << endl; }
};

int main()
{
	Dog d1;
	const Dog d2;
	d1.printDogName();
	d2.printDogName();
	return 0;
}

// 1.5 Describe the function below:
	const int* const fun(const int* const& p) const;

// 1.6 Edit the class so that getItem is a const function which returns
// 	   int, also increments the accessCounter.
//	   The following code wouldn't compile, repair it. Give two solutions.
#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;

class BigArray
{
	vector <int> v;
	int accessCounter;

public:
	int getItem(int index) const
	{
		accessCounter++;
		return v[index];
	}
};