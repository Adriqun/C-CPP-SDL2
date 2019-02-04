#include <iostream>
#include <type_traits>
using namespace std;

class A
{
public:
	A() = default;
	A(const A&) = delete;
};

template <class Type>
void swap(Type& a, Type& b)
{
	static_assert(std::is_copy_constructible<Type>::value, "Swap requires copying");
	auto c = b;
	b = a;
	a = c;
}

template <class Type>
struct Data
{
	static_assert(std::is_default_constructible<Type>::value,
		"Data requires default-constructible elements");
};

struct No_default
{
	No_default() = delete;
};

int main()
{
	A a1, a2;
	swap(a1, a2);	// error

	Data<int> ints;
	Data<No_default> defaults;	// error

	return 0;
}