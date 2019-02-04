#include <iostream>

template <typename Type>
Type max(Type a, Type b) {
	return a > b ? a : b;
}

int max(int a, int b) {
	return a > b ? a : b;
}



template<typename T1, typename T2>
auto max2(T1 a, T2 b)
{
	return b < a ? a : b;
}
template<typename RT, typename T1, typename T2>
RT max2(T1 a, T2 b)
{
	return b < a ? a : b;
}


int main()
{
	using namespace std;

	max(7, 42);		// calls max(int a, int b)
	max<>(7, 42);	// calls max(Type a, Type b)
	max(7.0, 42);	// calls max(int a, int b)

	auto a = ::max(4, 7.2);					// uses first
	auto b = ::max<long double>(7.2, 4);	// uses second
	auto c = ::max<int>(4, 7.2);			// (ERROR) both max2 functions are called

	return 0;
}

/*
#include <iostream>
// maximum of two values of any type:
template<typename T>
T max(T a, T b)
{
	std::cout << "max<T>() \n";
	return b < a ? a : b;
}
// maximum of three values of any type:
template<typename T>
T max(T a, T b, T c)
{
	return max(max(a, b), c); // uses the template version
	even for ints
} //because the following
declaration comes
// too late:
// maximum of two int values:
int max(int a,
	int b)
{
	std::cout << "max(int,int) \n";
	return b < a ? a : b;
}
int main()
{
	::max(47, 11, 33); // OOPS: uses max<T>() instead of
	max(int, int)
}
*/