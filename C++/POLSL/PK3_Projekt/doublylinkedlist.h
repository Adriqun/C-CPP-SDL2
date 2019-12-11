/*
	File: doublylinkedlist.h
	Author: Adrian Michalek
	Github: https://github.com/devmichalek
	Classes:
		Node				- represents node of type T in doubly linked list
							- keeps track of allocated memory

		Guard				- helper class - represents memory guard
							- saves current amount of allocated bytes when instantiated
							- compares deallocated bytes when destroyed
							- throws an error in case of lost bytes in particular stack frame

		DoublyLinkedList	- implementation of doubly linked list of type T
*/

#pragma once
#include <iostream>
#include <string>
#include <memory>

template<class T>
class Node
{
	// Here is the value to check memory allocated bytes.
	static __int64 m_allocated;

public:
	T m_data; // Stores data of type T
	Node<T>* m_prev; // Points to previous node
	Node<T>* m_next; // Points to next node

	explicit Node(T data, const Node<T>* prev = nullptr, const Node<T>* next = nullptr); // Constructor with parameters
	~Node(); // Destructor
	Node<T> operator=(Node<T>&& x); // Assignment operator

	void* operator new(size_t); // Operator new
	void operator delete(void*); // Operator delete
	static const __int64& allocated(); // Returns current number of allocated bytes
};

template<class T>
__int64 Node<T>::m_allocated = 0;

template<class T>
Node<T>::Node(T data, const Node<T>* prev, const Node<T>* next)
{
	m_data = data;
	m_prev = prev;
	m_next = next;
}

template<class T>
Node<T>::~Node()
{
	delete m_prev;
	delete m_next;
}

template<class T>
Node<T> Node<T>::operator=(Node<T>&& x)
{
	m_data = x.m_data;
	m_prev = x.m_prev;
	m_next = x.m_next;
}

template<class T>
void* Node<T>::operator new(size_t size)
{
	m_allocated += size;
	return malloc(size);
}

template<class T>
void Node<T>::operator delete(void* ptr)
{
	m_allocated -= sizeof(T);
	m_allocated -= (sizeof(Node<T>) * 2);
	free(ptr);
}

template<class T>
const __int64& Node<T>::allocated()
{
	return m_allocated;
}

// Helper class Guard protects from memory corruption.
class Guard
{
	__int64 m_allocated;
public:
	Guard()
	{
		m_allocated = Node<std::int8_t>::allocated();
	}
	~Guard()
	{
		try {
			if (Node<std::int8_t>::allocated() != m_allocated)
			{
				throw std::bad_alloc();
			}
		}
		catch (...)
		{
			std::string message = "Fatal error: Memory corruption, lost ";
			message += std::to_string(m_allocated - Node<std::int8_t>::allocated());
			message += " bytes...";
			std::cout << message << std::endl;
		}
	}
};

template<class T>
class DoublyLinkedList
{
	Node<T>* m_head;
	Node<T>* m_tail;
	uint64_t m_size;
	static const uint64_t m_max = 10000;

public:
	explicit DoublyLinkedList(); // Default constructor
	explicit DoublyLinkedList(const DoublyLinkedList<T>&); // Copy constructor (reference)
	explicit DoublyLinkedList(const DoublyLinkedList<T>&&); // Copy constructor (move semantics)
	~DoublyLinkedList(); // Destructor
	DoublyLinkedList<T>& operator=(const DoublyLinkedList<T>&); // Assignment operator (reference)
	DoublyLinkedList<T>& operator=(const DoublyLinkedList<T>&&); // Assignment operator (move semantics)
	void insert(const T&); // Creates new node, inserts new data
	void insert(const T&&); // Creates new node, inserts new data
	void insert(T); // Creates new node, inserts new data
	bool remove(uint64_t); // Removes node specified by index from the list
	bool remove(Node<T>*); // Removes node specified by address pointer from the list
	const T& front();
	bool pop_front();
	Node<T>* search(uint64_t); // Search by index, returns nullptr if node was not found
	uint64_t search(Node<T>*); // Search by node pointer address, returns std::numeric_limits<uint64_t>::max() in node was not found
	void clear(); // Removes all the data from the list
	uint64_t size(); // Returns number of nodes allocated for the list
	friend std::ostream& operator<<(std::ostream&, const DoublyLinkedList<T>&);
};

template<class T>
DoublyLinkedList<T>::DoublyLinkedList()
{
	m_size = 0;
	m_head = nullptr;
	m_tail = nullptr;
}

template<class T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>& rhs)
{
	clear();
	*this = rhs;
}

template<class T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>&& rhs)
{
	clear();
	*this = rhs;
}

template<class T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
	clear();
}

template<class T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList<T>& rhs)
{
	// Deep copy
}

template<class T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList<T>&& rhs)
{
	// Deep copy
}

template <class T>
void DoublyLinkedList<T>::insert(const T& data)
{
	try {
		++m_size;
		if (m_size > m_max)
		{
			throw std::overflow_error("Error: Unsigned 64-bit integer overflow, extend m_max range...");
		}
	}
	catch (const std::overflow_error& error)
	{
		std::cout << error.what();
	}

	if (!m_head)
	{	// insert first element.
		m_tail = m_head = new Node(data);
	}
	else
	{
		// Go to the end of the list.
		Node* node = m_head;
		while (node->m_next)
			node = node->m_next;

		// insert new node.
		Node* newNode = new Node(data, node->m_next);
		node->m_next = newNode;
		m_tail = newNode;
	}
}

template <class T>
void DoublyLinkedList<T>::insert(const T&& data)
{
	try {
		++m_size;
		if (m_size > m_max)
		{
			throw std::overflow_error("Error: Unsigned 64-bit integer overflow, extend m_max range...");
		}
	}
	catch (const std::overflow_error & error)
	{
		std::cout << error.what();
	}

	if (!m_head)
	{	// insert first element.
		m_tail = m_head = new Node(data);
	}
	else
	{
		// Go to the end of the list.
		Node* node = m_head;
		while (node->m_next)
			node = node->m_next;

		// insert new node.
		Node* newNode = new Node(data, node->m_next);
		node->m_next = newNode;
		m_tail = newNode;
	}
}

template <class T>
void DoublyLinkedList<T>::insert(T data)
{
	try {
		++m_size;
		if (m_size > m_max)
		{
			throw std::overflow_error("Error: Unsigned 64-bit integer overflow, extend m_max range...");
		}
	}
	catch (const std::overflow_error & error)
	{
		std::cout << error.what();
	}

	if (!m_head)
	{	// insert first element.
		m_tail = m_head = new Node(data);
	}
	else
	{
		// Go to the end of the list.
		Node* node = m_head;
		while (node->m_next)
			node = node->m_next;

		// insert new node.
		Node* newNode = new Node(data, node->m_next);
		node->m_next = newNode;
		m_tail = newNode;
	}
}

template <class T>
bool DoublyLinkedList<T>::remove(uint64_t index)
{
	if (!m_head)
		return false;

	if (index >= m_max)
		return false;

	Node<T>* node = m_head;
	while (index && node->m_next)
	{
		--index;
		node = node->m_next;
	}

	if (index)
		return false;

	if (!node)
		return false;

	--m_size;
	if (node->m_prev)
		node->m_prev->m_next = nullptr;
	if (node->m_next)
		node->m_next->m_prev = nullptr;

	delete node;
	node = nullptr;
	return true;
}

template <class T>
bool DoublyLinkedList<T>::remove(Node<T>* seek)
{
	if (!m_head)
		return false;

	if (!seek)
		return false;

	Node<T>* node = m_head;
	while (node)
	{
		if (node == seek)
			break;
		node = node->m_next;
	}

	if (!node)
		return false;

	--m_size;
	if (node->m_prev)
		node->m_prev->m_next = nullptr;
	if (node->m_next)
		node->m_next->m_prev = nullptr;

	delete node;
	node = nullptr;
	return true;
}

template <class T>
const T& DoublyLinkedList<T>::front()
{
	return m_head->m_data;
}

template <class T>
bool DoublyLinkedList<T>::pop_front()
{
	return remove(0);
}

template <class T>
Node<T>* DoublyLinkedList<T>::search(uint64_t index)
{
	if (!m_head)
		return nullptr;

	if (index >= m_max)
		return nullptr;

	Node<T>* node = m_head;
	while (index && node->m_next)
	{
		--index;
		node = node->m_next;
	}

	if (index)
		return nullptr;

	return node;
}

template <class T>
uint64_t DoublyLinkedList<T>::search(Node<T>* seek)
{
	if (!seek)
		return static_cast<uint64_t>(-1);

	uint64_t index = 0;
	Node<T>* node = m_head;
	while (node)
	{
		if (node == seek)
			return index;
		++index;
		node = node->m_next;
	}

	return static_cast<uint64_t>(-1);
}

template <class T>
void DoublyLinkedList<T>::clear()
{
	m_size = 0;

	Node<T>* tmp;
	Node<T>* node = m_head;
	while (node)
	{
		tmp = node;
		node = node->m_next;
		delete tmp;
	}

	m_head = nullptr;
	m_tail = nullptr;
}

template <class T>
uint64_t DoublyLinkedList<T>::size()
{
	return m_size;
}

template <class T>
std::ostream& operator<<(std::ostream& os, const DoublyLinkedList<T>& rhs)
{
	if (!rhs.m_head)
	{
		std::cout << "empty" << std::endl;
	}
	else
	{
		Node<T>* node = rhs.m_head;
		while (node)
		{
			std::cout << node->m_data << " ";
			node = node->m_next;
		}
		std::cout << std::endl;
	}
}