#include <stdexcept>
#include <vector>
#include <cassert>
#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;

// Abstract Class
class ContainerOfInts {
public:
	virtual const int getSize() = 0;
	virtual int& at(int i) = 0;
	virtual void printMe() = 0;
	ContainerOfInts() {}
	virtual ~ContainerOfInts()
	{
		cout << "ContainerOfInts Desctructor" << endl;
	}
};

// Derived Class
class Array :public ContainerOfInts {
	int size;
	int* ints;
public:
	Array(int size);
	~Array();
	const int getSize();
	int& at(int i);
	void printMe();
};

// Derived Class
class LinkedList :public ContainerOfInts {
	struct Node {
		int data;
		Node* next;
	};
	Node* head;
	int size;

public:
	LinkedList(int size);
	~LinkedList();
	const int getSize();
	int& at(int i);
	void add(int i);
	void printMe();

};

void doubleElement(ContainerOfInts& c);

int main()
{
	srand(time(NULL));
	int size = 10;
	ContainerOfInts* a = NULL;
	ContainerOfInts* b = NULL;

	a = new Array(size);
	b = new LinkedList(size+1);

	a->printMe();
	doubleElement(*a);
	a->printMe();

	b->printMe();
	doubleElement(*b);
	b->printMe();

	delete a;
	delete b;

	return 0;
}


void doubleElement(ContainerOfInts& c)
{
	for (int j = 0; j < c.getSize(); ++j) {
		c.at(j) *= 2;
	}
}


Array::Array(int size) {
	this->size = size;

	ints = new int[size];
	for (int j = 0; j < size; ++j) {
		ints[j] = rand()%10 +1;
	}
}

Array::~Array() {
	cout << "Array Destructor" << endl;

	if (ints != NULL) {
		delete[] ints;
		ints = NULL;
	}

	size = 0;
}

const int Array::getSize() {
	return size;
}

int& Array::at(int i) {
	if (i >= size || i < 0) {
		throw std::out_of_range("ArrayOfInts::at()");
	}
	
	return ints[i];
}

void Array::printMe() {
	cout << "Array: ";

	for (int j = 0; j < size; ++j) {
		cout << ints[j] << ", ";
	}

	cout << endl;
}


LinkedList::LinkedList(int size) {
	this->head = NULL;
	this->size = 0;
	while (--size) {
		add(rand()%10 +1);
	}
}

LinkedList::~LinkedList() {
	cout << "LinkedList Destructor" << endl;
	
	Node* current = this->head;
	while (current != 0) {
		Node* next = current->next;
		delete current;
		current = next;
	}
	size = 0;
}

const int LinkedList::getSize() {
	return size;
}

int& LinkedList::at(int i) {
	if (i >= size || i < 0) {
		throw std::out_of_range("LinkedList::at()");
	}

	Node* current = this->head;
	for (int j = 0; j < i; ++j) {
		current = current->next;
	}
	return current->data;
}

void LinkedList::add(int i) {
	Node* newNode = new Node;
	newNode->data = i;
	newNode->next = head;
	this->head = newNode;
	++this->size;
}

void LinkedList::printMe() {
	cout << "List:  ";
	
	for (int j = 0; j < size; ++j) {
		cout << at(j) << ", ";
	}

	cout << endl;
}