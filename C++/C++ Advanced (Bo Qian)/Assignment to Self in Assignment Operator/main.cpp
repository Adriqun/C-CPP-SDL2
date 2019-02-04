#include <iostream>
#include <string>
using namespace std;

class Dog
{
	int* pointer;
public:
	Dog() {};
	~Dog() {};
	void setPointer(int value) {
		pointer = new int(value);
	}
	int getPointer() {
		return *pointer;
	}
	Dog& operator=(const Dog& dog) {
		*this->pointer = *dog.pointer;
		return *this;
	}

	/*void operator=(const Dog& dog) {
		*this->pointer = *dog.pointer;
	}*/
};

int main()
{
	Dog dog1, dog2;
	dog1.setPointer(5);
	dog2.setPointer(6);

	dog1 = dog2;

	cout << dog1.getPointer();

	return 0;
}
