#include <iostream>

class Timer
{
public:
	Timer();
};

class TimeKeeper
{
public:
	TimeKeeper(const Timer& t);
	int get_time();
};

void f (double d)
{
	int i(int(d)); // Treated as function declaration.
	return i; // Won't compile.
}

int main()
{
	// The most vexing parse is a specific form of syntactic ambiguity resolution in the C++ programming language.
	// The term was used by Scott Meyers in Effective STL(2001).
	// It is formally defined in section 8.2 of the C++ language standard.

	TimeKeeper t(Timer()); // Treated as function declaration.
	return t.get_time(); // Won't compile.
}