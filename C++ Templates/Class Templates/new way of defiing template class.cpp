#include <iostream>
#include <vector>
using namespace std;

template<class Type>
class Animal
{
	vector<Type> data;
public:
	Animal() = default;
	Animal(Type piece) :data({ piece })
	{

	}
};

int main()
{
	Animal animal = "dog";

	return 0;
}