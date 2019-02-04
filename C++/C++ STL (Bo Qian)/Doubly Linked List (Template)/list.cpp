#include "list.h"
#include "animal.h"

template<class Data>
List<Data>::Node::Node(Data* data)
{
	this->data = data;
	next = nullptr;
	prev = nullptr;
}

template<class Data>
List<Data>::Node::~Node()
{
	if (data != nullptr)
	{
		delete data;
		data = nullptr;
	}
}



template<class Data>
List<Data>::List()
{
	counter = 0;
	head = nullptr;
	tail = nullptr;
}

template<class Data>
List<Data>::~List()
{
	counter = 0;

	if (!empty())
	{
		Node* node = head;
		Node* delNode;
		while (node->next != nullptr)
		{
			delNode = node;
			node = node->next;
			delNode->next = nullptr;
			delNode->prev = nullptr;
		}
	}
}

template<class Data>
int& List<Data>::size()
{
	return counter;
}

template<class Data>
bool List<Data>::empty()
{
	return head == nullptr;
}



template<class Data>
bool List<Data>::push_back(Data* data)
{
	if (search(data) != nullptr)
	{
		return false;
	}

	++counter;
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
	

	return true;
}

template<class Data>
bool List<Data>::push_front(Data* data)
{
	if (search(data) != nullptr)
	{
		return false;
	}

	++counter;
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

	return true;
}

template<class Data>
bool List<Data>::pop_back()
{
	if (tail != nullptr)
	{
		if (tail == head)
			head = nullptr;

		Node* delNode = tail;
		tail = tail->prev;
		

		if (tail != nullptr)
			tail->next = nullptr;

		delete delNode;
		--counter;
		return true;
	}

	return false;
}

template<class Data>
bool List<Data>::pop_front()
{
	if (head != nullptr)
	{
		if (head == tail)
			tail = nullptr;
			
		Node* delNode = head;
		head = head->next;

		if (head != nullptr)
			head->prev = nullptr;
			
		delete delNode;
		--counter;
		return true;
	}

	return false;
}



template<class Data>
typename List<Data>::Node* &List<Data>::begin()
{
	return head;
}

template<class Data>
typename List<Data>::Node* &List<Data>::end()
{
	return tail;
}

template<class Data>
typename List<Data>::Node* List<Data>::search(Data* data)
{
	if (empty() || data == nullptr)
	{
		return nullptr;
	}

	Node* node = head;
	while (node->next != nullptr)
	{
		if (node->data->operator==(data))
		{
			break;
		}

		node = node->next;
	}

	if (node->data->operator==(data))
	{
		return node;
	}

	return nullptr;
}



template<class Data>
bool List<Data>::erase(Node* node)
{
	if (node == nullptr)
		return false;

	if (node == head)
	{
		pop_front();
		return true;
	}
	else if (node == tail)
	{
		pop_back();
		return true;
	}
	else
	{
		--counter;
		Node* delNode = node;
		node->prev->next = node->next;
		delete delNode;
		return true;
	}

	return false;
}

template<class Data>
bool List<Data>::erase(Data* data)
{
	Node* node = search(data);

	if (node == nullptr)
		return false;

	if (node == head)
	{
		pop_front();
		return true;
	}
	else if (node == tail)
	{
		pop_back();
		return true;
	}
	else
	{
		--counter;
		Node* delNode = node;
		node->prev->next = node->next;
		delete delNode;
		return true;
	}

	return false;
}

template<class Data>
void List<Data>::swap(List* &list)
{
	Node* head_supp = head;
	Node* tail_supp = tail;
	int size_supp = counter;

	head = list->begin();
	tail = list->end();
	counter = list->size();

	list->begin() = head_supp;
	list->end() = tail_supp;
	list->size() = size_supp;
}



template<class Data>
void List<Data>::print()
{
	Node* node = head;

	while (node != nullptr)
	{
		std::cout << node->data << std::endl;
		node = node->next;
	}
}

template<class Data>
void List<Data>::print(Node* node)
{
	if (node != nullptr)
	{
		std::cout << node->data << std::endl;
	}
}

template class List<Animal>;