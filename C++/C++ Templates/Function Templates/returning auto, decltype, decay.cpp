#include <iostream>

// The function returns the type of higher value.
template <typename T1, typename T2>
auto max(T1 a, T2 b) -> decltype(a > b ? a : b) {
	return a > b ? a : b;
}

// In case of reference value, here is an explanation.
#include <type_traits>
template <typename T1, typename T2>
auto min(T1 a, T2 b) -> typename std::decay<decltype(a < b ? a : b)>::type {
	return a < b ? a : b;
}

int main()
{
	using namespace std;

	cout << max(50, 4.28) << endl;
	cout << max(14.88, 10) << endl;

	int a = 11;
	int& aRef = a;
	cout << min(aRef, 14.22) << endl;

	return 0;
}