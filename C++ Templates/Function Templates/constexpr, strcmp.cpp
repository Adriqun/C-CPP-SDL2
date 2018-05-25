#include <iostream>

int main()
{
	using namespace std;

	// Error
	int a;
	cin >> a;
	constexpr int b = a;

	// Good
	constexpr int c = 5;
	// constexpr makes variable a must to have a ascribed value in compilation time

	string aa = "aa";
	string bb = "aa";

	if (strcmp(aa, bb)) {
		cout << "yup";
	}

	return 0;
}
