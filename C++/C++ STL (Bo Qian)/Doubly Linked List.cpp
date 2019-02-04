#include <iostream>

struct Node
{
	int data;
	Node* next;
	Node* prev;

	Node(int data = 0);
	~Node();
};

class List
{
	int _size;
	Node* head;
	Node* tail;

public:
	List();
	~List();
	int size();
	bool empty();
	void print();

	void push_back(int data);
	void push_front(int data);
	void pop_back();
	void pop_front();
	void erase(int data);

	Node* &begin();
	Node* &end();
	void swap(List* &list);
};


int main()
{
	List* list = new List;
	
	list->print();

	list->push_back(5);
	list->push_back(10);
	list->push_front(15);
	list->print();
	std::cout << std::endl;

	// Test.
	List* list2 = new List;
	list2->swap(list);

	list2->erase(5);
	list2->print();
	std::cout << std::endl;

	

	list2->erase(10);
	list2->print();


	delete list;
	list = nullptr;

	delete list2;
	list2 = nullptr;

	return 0;
}



Node::Node(int data)
{
	this->data = data;
	next = nullptr;
	prev = nullptr;
}

Node::~Node()
{
	data = 0;
}



List::List()
{
	_size = 0;
	head = nullptr;
	tail = nullptr;
}

List::~List()
{
	_size = 0;

	Node* node;
	while (head != nullptr)
	{
		node = head->next;
		delete head;
		head = node;
	}
}

int List::size()
{
	return _size;
}

bool List::empty()
{
	return head == nullptr;
}

void List::print()
{
	Node* node = head;
	while (node != nullptr)
	{
		std::cout << node->data << " ";
		node = node->next;
	}
}

void List::push_back(int data)
{
	++_size;
	Node* newNode = new Node(data);

	if (tail != nullptr)
	{
		tail->next = newNode;
	}

	newNode->prev = tail;
	tail = newNode;

	if (head == nullptr)
	{
		head = tail;
	}
}

void List::push_front(int data)
{
	++_size;
	Node* newNode = new Node(data);

	if (head != nullptr)
	{
		head->prev = newNode;
	}

	newNode->next = head;
	head = newNode;

	if (tail == nullptr)
	{
		tail = head;
	}
}

void List::pop_back()
{
	if (tail != nullptr)
	{
		--_size;
		Node* node = tail;
		tail = tail->prev;

		if (tail != nullptr)
		{
			tail->next = nullptr;
		}

		delete node;
	}
}

void List::pop_front()
{
	if (head != nullptr)
	{
		--_size;
		Node* node = head;
		head = head->next;

		if (head != nullptr)
		{
			head->prev = nullptr;
		}

		delete node;
	}
}

void List::erase(int data)
{
	Node* node = head;
	while (node->next != nullptr && node->data != data)
	{
		node = node->next;
	}

	if (node->data == data)
	{
		if (node == head)		pop_front();
		else if (node == tail)	pop_back();
		else
		{
			--_size;
			node->prev->next = node->next;
			node->next->prev = node->prev;
			delete node;
		}
	}
}

Node* &List::begin()
{
	return head;
}

Node* &List::end()
{
	return tail;
}

void List::swap(List* &list)
{
	Node* head_supp = head;
	Node* tail_supp = tail;

	head = list->begin();
	tail = list->end();

	list->begin() = head_supp;
	list->end() = tail_supp;
}