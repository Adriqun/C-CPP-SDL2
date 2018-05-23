#include <vector>
#include <iostream>
#include <string>

using namespace std;

struct Sth {
	int a;
	string b;
	Sth(int a, string b) {
		this->a = a;
		this->b = b;
	}
};


int main()
{
	vector <Sth> vec;
	vector <Sth> ::iterator it = vec.begin();

	vec.emplace(it, 4, "Ann");			// constructs inside of the vector <- faster
	it = vec.begin();
	vec.insert(it, Sth(3, "Jason"));	// copies object into the vector, sometimes doesn't copy but move


	vec.emplace_back(10, "Garry");		// reccommended but do not use with tuple! <- faster
	vec.push_back(Sth(6, "Gabrielle"));

	return 0;
}