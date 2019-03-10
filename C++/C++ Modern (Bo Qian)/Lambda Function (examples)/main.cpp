// 1.
#include <iostream>
#include <vector>

template<typename func>
void filter(func f, std::vector<int> arr) {
	for (auto i : arr) {
		if (f(i))
			std::cout << i << " ";
	}
}

int main()
{
	std::vector<int> v = { 1, 2, 3, 4, 5, 6 };
	filter([](int &x) { return x > 3; }, v);
	return 0;
}

// 2.
int main()
{
	int lp = 0;
	auto raport = [lp](const char* msg) mutable
	{
		std::cout << msg << ++lp << " ";
	};

	raport("A ");
	raport("B ");
	return 0;
}

// 3.
int main()
{
	int a = 0, b = 1, c = 2, d = 3;
	auto f1 = [&a]() { a = 1; printf("%d\n", a); };
	auto f2 = [=]() { printf("%d\n", a + b + c + d); };
	auto f3 = [&, b]() { a = c = d; printf("%d\n", b); };
	//&-pass all variables by reference(with variable : &variable)
	//= -pass all variables by const copy(with variable : variable)
	return 0;
}