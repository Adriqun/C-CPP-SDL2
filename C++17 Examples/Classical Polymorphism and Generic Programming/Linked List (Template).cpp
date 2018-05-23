#include <iostream>
#include <string>

using namespace std;

// Linked list implementation.
template <class Type>
class List {
	typedef struct Node {
		Type data;
		Node* next;
	}* NodePtr;

	// The code above is equil to: typedef struct Node* NodePtr;

	int size;
	NodePtr head;
	NodePtr current;
	NodePtr temporary;

public:
	List();
	~List();
	void add(Type data);
	void remove(Type data); // search and delete
	void print();
	const int& getSize() const;
};

template <class Type>
List<Type>::List() {
	size = 0;
	head = nullptr;
	current = nullptr;
	temporary = nullptr;
}

template <class Type>
List<Type>::~List() {
	size = 0;
	while (current != nullptr) {
		NodePtr node = current->next;
		current = node;
		delete node;
	}

	if (head != nullptr) {
		delete head;
		head = nullptr;
	}
}

template <class Type>
void List<Type>::add(Type data) {
	NodePtr newNode = new Node;
	newNode->next = nullptr;
	newNode->data = data;

	if (head != nullptr) {
		current = head;
		while (current->next != nullptr) {
			current = current->next;
		}

		current->next = newNode;	// ascribing the last element
	}
	else {
		head = newNode;				// making a front
	}

	++size;
}

template <class Type>
void List<Type>::remove(Type data) {
	temporary = head;
	current = head;

	while (current != nullptr && current->data != data) {
		temporary = current;
		current = current->next;
	}

	if (current == nullptr) {
		cout << data << " was not in the list." << endl;
	}
	else {
		NodePtr removedNode = current;
		current = current->next;
		temporary->next = current;

		if (removedNode == head) {
			head = head->next;
			temporary = nullptr;
		}

		delete removedNode;
		--size;
	}
}

template <class Type>
void List <Type>::print() {
	current = head;
	while (current != nullptr) {
		cout << current->data << endl;
		current = current->next;
	}
}

template <class Type>
const int& List<Type>::getSize() const {
	return size;
}

int main()
{
	List <string>* list = new List <string>;
	list->add("Jane");
	list->add("Garry");
	list->add("David");
	list->print();
	list->remove("Garry");
	list->print();
	delete list;

	list = new List <string>;
	list->add("Hippo");
	list->add("Dog");
	list->print();
	list->remove("Dog");
	list->print();
	delete list;

	return 0;
}