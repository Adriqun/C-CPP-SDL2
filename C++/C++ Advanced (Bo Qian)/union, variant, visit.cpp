// c++_17
// example of union, variant and visit

#include <iostream>
#include <string>
#include <vector>
#include <variant>

union MultiType
{
	std::string a;
	int b;
	float c;
	std::vector<double> vec;

	~MultiType() {}
};


int main()
{
	MultiType a = { "hello" };
	a.b = 5;
	std::cout << "a: " << a.a << std::endl;
	std::cout << "b: " << a.b << std::endl;

	new (&a.vec) std::vector<double>;
	a.vec.push_back(10.00);
	std::cout << "vec[0]: " << a.vec[0] << std::endl;


	std::variant<char, int, double> v;
	v = 'x';

	//std::visit([](auto x) { std::cout << x << std::endl; }, v);


	return 0;
}