#include <vector>
#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>

using namespace std;


template<class Container, class Predicate>
int count_if(const Container& container, Predicate predicate)
{
	int sum = 0;
	for (auto &it :container) {
		if (predicate(it)) {
			++sum;
		}
	}
	return sum;
}

bool AboveZero(int e) {
	return e > 0 ? true : false;
}


int main()
{
	std::vector<int> v = { 3, 1, -4, 1, 5, 9, -2, -6 };

	int above = count_if(v, AboveZero );
	int below = count_if(v, [](int e) { return e < 0; });

	cout << "Above: " << above << "\nBelow: " << below;

	return 0;
}