#include <iostream>
using namespace std;

// C++11 Delete copy constructor and copy assignment operator
class A
{
public:
	A() {}
	A(const A&) = delete;
	void operator=(const A&) = delete;
};

// Private copy constructor and copy assignment operator
class B
{
	B(const B&);
	B& operator=(const B&);
public:
	B() {}
};

int main()
{
	A a1, a2;
	B b1, b2;

	a1 = a2;	// Error: accessing deleted function
	b1 = b2;	// Error: accessing private function

	return 0;
}