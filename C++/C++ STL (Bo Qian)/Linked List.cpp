#include <iostream>

struct Node
{
	int data;
	Node* next;

	Node(int data = 0);
	~Node();
};

class List
{
	int _size;
	Node* _head;

public:

	List();
	~List();
	int size();
	bool empty();

	void add(int data);
	void remove(int data);

	Node* &head();
	void swap(List* &list);
	void print();
};


int main()
{
	List* list = new List;

	std::cout << "0.\n";
	list->print();
	std::cout << std::endl;

	std::cout << "1.\n";
	list->add(15);
	list->add(31);
	list->add(9);
	list->print();
	std::cout << std::endl;

	// Test.
	List* list2 = new List;
	list2->swap(list);

	delete list;
	list = nullptr;

	std::cout << "2.\n";
	list2->remove(31);
	list2->print();
	std::cout << std::endl;

	std::cout << "3.\n";
	list2->remove(15);
	list2->remove(9);
	list2->print();
	std::cout << std::endl;

	delete list2;
	list2 = nullptr;

	return 0;
}



Node::Node(int data)
{
	this->data = data;
	next = nullptr;
}

Node::~Node()
{
	data = 0;
}



List::List()
{
	_size = 0;
	_head = nullptr;
}

List::~List()
{
	_size = 0;
	Node* node = _head;
	Node* delNode;
	while (node != nullptr)
	{
		delNode = node;
		node = node->next;
		delNode->next = nullptr;
		delete delNode;
	}

}

int List::size()
{
	return _size;
}

bool List::empty()
{
	return _head == nullptr;
}

void List::add(int data)
{
	++_size;
	Node* newNode = new Node(data);

	if (_head == nullptr)
	{
		_head = newNode;
	}
	else
	{
		Node* node = _head;
		while (node->next != nullptr)
		{
			node = node->next;
		}

		node->next = newNode;
	}
}

void List::remove(int data)
{
	if (empty())	return;

	Node* node = _head;
	Node* previous = _head;

	while (node->next != nullptr)
	{
		if (node->data == data)
			break;

		previous = node;
		node = node->next;
	}

	if (node->data == data)
	{
		--_size;
		Node* delNode = node;
		previous->next = node->next;

		if (node == _head)
		{
			_head = _head->next;
		}

		delete delNode;
	}
}

Node* &List::head()
{
	return _head;
}

void List::swap(List* &list)
{
	Node* supp = _head;
	_head = list->head();
	list->head() = supp;
}

void List::print()
{
	Node* node = _head;
	while (node != nullptr)
	{
		std::cout << "Value: " << node->data << std::endl;
		node = node->next;
	}
}