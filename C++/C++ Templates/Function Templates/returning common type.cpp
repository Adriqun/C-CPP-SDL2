#include <iostream>
#include <type_traits>

// Since C++11
/*template <typename T1, typename T2>
typename std::common_type<T1, T2>::type max(T1 a, T2 b) {
	return a > b ? a : b;
}*/

template <typename T1, typename T2>
std::common_type_t<T1, T2> max(T1 a, T2 b) {
	return a > b ? a : b;
}

int main()
{
	using namespace std;

	cout << ::max(15, 10.00) << endl;
	cout << ::max(1.896, 1) << endl;

	return 0;
}