#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace std;

class ArrayOfInts {
	int size;
	int* ints;

public:
	ArrayOfInts(int size);
	~ArrayOfInts();
	void printMe();
	const int getSize() const;
	int& at(int i);
};

void doubleElements(ArrayOfInts& a) {
	for (int j = 0; j < a.getSize(); j++) {
		a.at(j) *= 2;
	}
}

int main()
{
	srand(time(NULL));

	ArrayOfInts* a = new ArrayOfInts(10);
	a->printMe();
	doubleElements(*a);
	a->printMe();
	delete a;

	return 0;
}

ArrayOfInts::ArrayOfInts(int size) {
	this->size = size;
	ints = new int[size];
	for (int j = 0; j < size; ++j) {
		ints[j] = rand() % 10 + 1;
	}
}

ArrayOfInts::~ArrayOfInts() {
	if (ints != NULL)
	{
		delete[] ints;
		ints = NULL;
	}

	size = 0;
}

void ArrayOfInts::printMe() {
	for (int j = 0; j < size; ++j) {
		cout << ints[j] << ", ";
	}

	cout << endl;
}

const int ArrayOfInts::getSize() const {
	return size;
}

int& ArrayOfInts::at(int i) {
	return ints[i];
}