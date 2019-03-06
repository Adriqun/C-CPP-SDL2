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

// 1.6 Edit the class so that getItem is a const function that returns v[index]
// 	   and increments the accessCounter.
//	   The following code wouldn't compile, repair it. Give two solutions.
#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;

class BigArray
{
	vector<int> v;
	int accessCounter;

public:
	int getItem(int index) const
	{
		accessCounter++;
		return v[index];
	}
};

// 1.7 Predict the output of console for:
#include <stdio.h>
void fun(char **p)
{
	char* t;
	t = (p += sizeof(int))[-1];
	printf("%s\n", t);
}

int main()
{
	const char* argv[] = { "ab", "cd", "ef", "gh", "ij", "kl" };
	fun((char**)argv);
	return 0;
}

// 1.8 What is the output for the following code?
#include <stdio.h>
int main()
{
	int a[][3] = { 1, 2, 3, 4, 5, 6 };
	int(*ptr)[3] = a;
	printf("%d %d ", (*ptr)[1], (*ptr)[2]);
	++ptr;
	printf("%d %d\n", (*ptr)[1], (*ptr)[2]);
	return 0;
}


// 2.1 Disallow copy constructor in the following code.
// 	   Give at least two solutions. Do not change/add other behaviours.
#include <string>
#include <iostream>

struct Human
{
	Human(std::string name) { std::cout << "My name is " << name << std::endl; }
};

int main(int argc, char **argv)
{
	Human h1(std::string("John"));
	Human h2(h1); // copy constructor shouldn't compile
	return 0;
}


// 2.2 Keep ~Human() private add mechanism of freeing memory at the same time
// 	   in the following code. Do not change/add other behaviours.
#include <string>
#include <iostream>

class Human
{
	~Human() { std::cout << "Goodbye" << std::endl; }
public:
	Human(std::string name) { std::cout << "My name is " << name << std::endl; }
};

int main(int argc, char **argv)
{
	Human* of = new Human("name");
	return 0;
}

// 2.3 What is the output of the following code?
#include <string>
#include <iostream>

struct Cat
{
	Cat() { std::cout << "A"; }
	Cat(std::string str) { std::cout << str; }
};

struct Dog
{
	Dog(std::string str) { std::cout << str; }
};

int main(int argc, char **argv)
{
	Cat c1("B");
	Dog d1;
	Cat c2("A");
	Cat c3;
	Dog d2("C");
	return 0;
}

// 2.4 Change the DogFactory's function createYellowDog() so that there is no
// 	   need to use virtual keyword in parent class.
//	   Hint: use shared_ptr.
#include <memory>
struct Dog
{
	/*virtual*/ ~Dog() {}
};

struct Yellowdog : public Dog
{
	~Yellowdog() {}
};

struct DogFactory
{
	//static Dog* createYellowDog() { return new Yellowdog(); }
};

// 2.5 What is the difference between malloc(), calloc() and realloc()?

// 2.6 Implement safe self assignment operator. Give two solutions.
//	   Do deleting c(Collar) before creating new Collar is safe?
class Collar;
class Dog {
	Collar* c;
	Dog& operator=(const Dog &rhs) {
		// wouldn't work when
		// Dog a;
		// a = a;

		delete c;
		c = new Collar(*rhs.c);
		return *this;
	}
}

// 2.7 What is the output of the following program?
#include <stdio.h>
#define R 10
#define C 20

int main()
{
	int* p[R][C];
	printf("%d", sizeof(*p));
	return 0;
}

// 2.8 What is the output of the following executed code?
#include <stdio.h>
struct Block {
	int a[3] = { 1, 2, 3 };
	int b[3] = { 4, 5, 6 };
	unsigned char ch[4] = {0, 1, 0, 0};
	int c[3] = { 7, 8, 9 };
};

int main()
{
	Block block;
	int* ptr = (int*)(&block.b + 1);
	printf("%d %d %d", *(block.b + 1), *(ptr - 1), *ptr);
	return 0;
}

// 2.9 What # prefix does in the following code?
// 	   What is the output for the following program?
#include <iostream>
#define watch(x) std::cout << #x << " is " << x << "\n";

int main()
{
	int i = 0xFF;
	int* j = &i;
	watch(i);
	watch(*j);
	return 0;
}

// 3.0 What does the explicit keyword mean?