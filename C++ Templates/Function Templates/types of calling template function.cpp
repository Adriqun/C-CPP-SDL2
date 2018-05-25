#include <iostream>

// One type template function
template <typename Type>
Type max(Type a, Type b) {
	return a > b ? a : b;
}

// That's how we can call empty function.
template <typename Type = std::string>
void func(Type a = "")
{
	// sth
}

// Let's have fun
template <typename RT, typename T1, typename T2>
RT fun(T1 a, T2 b) {
	// sth
}

int main()
{
	using namespace std;

	// calling with two different types
	cout << ::max<double>(5, 4.567) << endl;
	cout << ::max(5, static_cast<int> (4.567)) << endl;

	func("nah");	// ok
	func(1);		// ok
	func();			// ok

	fun<double, int, int>(3, 120);
	fun<int>(5.2, 48.99);

	return 0;
}