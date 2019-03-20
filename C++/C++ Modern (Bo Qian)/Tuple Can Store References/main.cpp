#include <iostream>
#include <tuple>
#include <string>

int main()
{
	using namespace std;
	
	string str = "penny";
	tuple<string&> t1(str);
	t1 = make_tuple(ref(str));
	get<0>(t1) = "pound";
	auto t2 = make_tuple(12, "curiosity", 'a');
	
	int x;
	string y;
	char z;
	make_tuple(ref(x), ref(y), ref(z)) = t2;
	std::tie(x, y, z) = t2;
	std::tie(x, std::ignore, z) = t2;

	auto t3 = std::tuple_cat(t1, t2);
	std::cout << std::tuple_size<decltype(t3)>::value << endl;
	std::tuple_element<1, decltype(t3)>::type a; // a is a string
	return 0;
}