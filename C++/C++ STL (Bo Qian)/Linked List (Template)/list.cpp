#include "list.h"
#include "person.h"
#include <iostream>

template<class Object>
List<Object>::Node::Node()
{
	object = nullptr;
	next = nullptr;
}

template<class Object>
List<Object>::Node::~Node()
{
	if (object != nullptr)
	{
		delete object;
		object = nullptr;
	}
}



template<class Object>
List<Object>::List()
{
	_size = 0;
	head = nullptr;
}

template<class Object>
List<Object>::~List()
{
	free();
}

template<class Object>
void List<Object>::free()
{
	_size = 0;
	Node* node = head;
	while (node != nullptr)
	{
		Node* delNode = node;
		node = node->next;
		delete delNode;
	}
}



template<class Object>
void List<Object>::add(Object* object)
{
	if (head == nullptr)
	{
		head = new Node();
	}
	
	if(head != nullptr)
	{
		Node* node = head;
		while (node->next != nullptr)
		{
			node = node->next;
		}

		node->next = new Node();
		node->next->object = object;
		++_size;
	}
}

template<class Object>
bool List<Object>::remove(Object* object)
{
	if (empty())
	{
		return false;
	}

	Node* before = head;
	Node* node = head;
	while (node != nullptr)
	{
		before = node;
		node = node->next;

		if (object->operator==(node->object))
			break;
	}

	if (node != nullptr)
	{
		Node* delNode = node;
		before->next = node->next;
		delete delNode;
		--_size;

		return true;
	}

	return false;
}



template<class Object>
void List<Object>::print()
{
	if (!empty() && head != nullptr)
	{
		Node* node = head->next;
		while (node != nullptr)
		{
			std::cout << node->object;
			node = node->next;
		}
	}
}

template<class Object>
int List<Object>::size()
{
	return _size;
}

template<class Object>
bool List<Object>::empty()
{
	return _size == 0;
}

template class List <Person>;