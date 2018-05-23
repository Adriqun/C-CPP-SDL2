#include <vector>
#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>

using namespace std;

struct Person {
	int age;
	string name;
	string surname;
	Person(string name, string surname, int age) {
		this->name = name;
		this->surname = surname;
		this->age = age;
	}

	~Person() {
		name = "";
		surname = "";
		age = 0;
	}
};

class LinkedList {
	struct Node {
		Person* person = nullptr;
		Node* next;
	};

	int length;
	Node* head;
public:

	void free();
	LinkedList();
	~LinkedList();

	Person* at(int i);
	void add(Person* person);
	const int getLength() const;
	
	void deleteLast();
	void deleteFirst();
};



void LinkedList::free() {
	Node* current = head;
	while (current != nullptr)
	{
		Node* next = current->next;

		if (current->person != nullptr) {
			delete current->person;
			current->person = nullptr;
		}

		delete current;
		current = next;
	}

	length = 0;
}

LinkedList::LinkedList() {
	length = 0;
	head = nullptr;
}

LinkedList::~LinkedList() {
	free();
}



Person* LinkedList::at(int i) {
	i = length - i -1;
	if (i < 0 || i >= length) {
		return nullptr;
	}
	
	Node* node = head;
	for (int j = 0; j < i; ++j) {
		node = node->next;
	}
	
	return node->person;
}

void LinkedList::add(Person* person) {
	Node* newNode = new Node;
	newNode->person = person;
	newNode->next = head;
	head = newNode;
	++length;
}

const int LinkedList::getLength() const {
	return length;
}



void LinkedList::deleteFirst() {
	Node* node = head;
	for (int j = 0; j < length -2; ++j) {
		node = node->next;
	}

	// Delete person.
	if (node->person != nullptr) {
		delete node->person;
		node->person = nullptr;
	}

	// Delete node.
	delete node;

	--length;
}

void LinkedList::deleteLast() {
	Node* node = head;
	head = head->next;

	// Delete person.
	if (node->person != nullptr) {
		delete node->person;
		node->person = nullptr;
	}

	// Delete node.
	delete node;

	--length;
}



int main()
{
	LinkedList* l = new LinkedList;
	l->add(nullptr);	// first element
	l->add(new Person("Danuta", "Michalek", 42));
	l->add(new Person("Wojciech", "Michalek", 41));
	l->add(new Person("Patrycja", "Michalek", 18));

	l->deleteFirst();
	for (int j = 0; j < l->getLength(); ++j) {
		Person* p = l->at(j);
		if (p != nullptr) {
			cout << p->name << " " << p->surname << " " << p->age << endl;
		}
	}

	return 0;
}