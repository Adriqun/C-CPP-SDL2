/*
	File: doublylinkedlist.h
	Author: Adrian Michalek
	Github: https://github.com/devmichalek
	Github (directly): https://github.com/devmichalek/Tutorials/tree/master/C%2B%2B/POLSL/PK3_Projekt
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

	explicit Node(T, Node<T>* = nullptr, Node<T>* = nullptr); // Constructor with parameters
	~Node(); // Destructor
	Node<T> operator=(const Node<T>&); // Assignment operator

	void* operator new(std::size_t); // Operator new
	void operator delete(void*); // Operator delete
	static const __int64& allocated(); // Returns current number of allocated bytes
};

template<class T>
__int64 Node<T>::m_allocated = 0;

template<class T>
Node<T>::Node(T data, Node<T>* prev, Node<T>* next)
{
	m_data = data;
	m_prev = prev;
	m_next = next;
}

template<class T>
Node<T>::~Node()
{
	// Not needed actually...
	m_prev = nullptr;
	m_next = nullptr;
}

template<class T>
Node<T> Node<T>::operator=(const Node<T>& rhs)
{
	m_data = rhs.m_data;
	return *this;
}

template<class T>
void* Node<T>::operator new(std::size_t size)
{
	m_allocated += size;
	return malloc(size);
}

template<class T>
void Node<T>::operator delete(void* ptr)
{
	// Type with size less than 1 byte will be converted into 4 byte type
	// automatically by compiler (memory alignment issue)
	m_allocated -= sizeof(T) < sizeof(void*) ? sizeof(void*) : sizeof(T);
	m_allocated -= (sizeof(Node<T>*) * 2);
	free(ptr);
}

template<class T>
const __int64& Node<T>::allocated()
{
	return m_allocated;
}

// Helper class Guard protects from memory corruption.
template<class T, bool throwException = true>
class Guard
{
	__int64 m_allocated;
public:
	Guard()
	{
		m_allocated = Node<T>::allocated();
	}
	~Guard()
	{
		if (throwException)
		{
			try {
				if (Node<T>::allocated() != m_allocated)
				{
					throw std::bad_alloc();
				}
			}
			catch (...)
			{
				std::string message = "Fatal error: Memory corruption, lost ";
				message += std::to_string(Node<T>::allocated() - m_allocated);
				message += " bytes...";
				std::cerr << message << std::endl;
			}
		}
		else
		{
			if (Node<T>::allocated() != m_allocated)
			{
				std::string message = "Fatal error: Memory corruption, lost ";
				message += std::to_string(Node<T>::allocated() - m_allocated);
				message += " bytes...";
				std::cout << message << std::endl;
			}
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
	DoublyLinkedList(const DoublyLinkedList<T>&); // Copy constructor (reference)
	DoublyLinkedList(const DoublyLinkedList<T>&&); // Copy constructor (move semantics)
	~DoublyLinkedList(); // Destructor
	DoublyLinkedList<T>& operator=(const DoublyLinkedList<T>&); // Assignment operator (reference)
	DoublyLinkedList<T>& operator=(const DoublyLinkedList<T>&&); // Assignment operator (move semantics)
	DoublyLinkedList<T>& operator+=(const DoublyLinkedList<T>&);
	DoublyLinkedList<T>& operator+=(const DoublyLinkedList<T>&&);
	bool insert(const T&); // Creates new node, inserts new data
	bool insert(const T&&); // Creates new node, inserts new data
	bool remove(uint64_t); // Removes node specified by index from the list
	bool remove(const Node<T>*); // Removes node specified by address pointer from the list
	const T& front() const; // Returns data form the head
	const T& back() const; // Returns data form the tail
	bool pop_front(); // Removes first node
	const Node<T>* head() const; // Returns head
	const Node<T>* tail() const; // Returns tail
	//Node<T>* search(uint64_t); // Search by index, returns nullptr if node was not found
	//uint64_t search(const Node<T>*); // Search by node pointer address, returns std::numeric_limits<uint64_t>::max() in node was not found
	void clear(); // Removes all the data from the list
	uint64_t size() const; // Returns number of nodes allocated for the list
	uint64_t max() const; // Returns max possible number of nodes allocated for the list

	template<class U> // << operator
	friend std::ostream& operator<<(std::ostream&, const DoublyLinkedList<U>&);
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
	*this = rhs;
}

template<class T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>&& rhs)
{
	*this = std::move(rhs);
}

template<class T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
	clear();
}

template<class T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList<T>& rhs)
{
	clear();
	Node<T>* node = rhs.m_head;
	while (node)
	{
		insert(node->m_data);
		node = node->m_next;
	}

	return *this;
}

template<class T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList<T>&& rhs)
{
	clear();
	Node<T>* node = rhs.m_head;
	while (node)
	{
		insert(node->m_data);
		node = node->m_next;
	}

	return *this;
}

template<class T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator+=(const DoublyLinkedList<T>& rhs)
{
	Node<T>* node = rhs.m_head;
	while (node)
	{
		insert(node->m_data);
		node = node->m_next;
	}

	return *this;
}

template<class T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator+=(const DoublyLinkedList<T>&& rhs)
{
	Node<T>* node = rhs.m_head;
	while (node)
	{
		insert(node->m_data);
		node = node->m_next;
	}

	return *this;
}

template <class T>
bool DoublyLinkedList<T>::insert(const T& data)
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
		std::cerr << error.what();
		return false;
	}

	if (!m_head)
	{	// Insert first node.
		m_tail = m_head = new Node<T>(data);
	}
	else
	{
		// Go to the end of the list.
		Node<T>* node = m_head;
		while (node->m_next)
			node = node->m_next;

		// Insert new node.
		Node<T>* newNode = new Node<T>(data, node);
		node->m_next = newNode;
		m_tail = newNode;
	}

	return true;
}

template <class T>
bool DoublyLinkedList<T>::insert(const T&& data)
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
		std::cerr << error.what();
		return false;
	}

	if (!m_head)
	{	// Insert first element.
		m_tail = m_head = new Node<T>(data);
	}
	else
	{
		// Go to the end of the list.
		Node<T>* node = m_head;
		while (node->m_next)
			node = node->m_next;

		// Insert new node.
		Node<T>* newNode = new Node<T>(data, node);
		node->m_next = newNode;
		m_tail = newNode;
	}

	return true;
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
		node->m_prev->m_next = node->m_next;
	if (node->m_next)
		node->m_next->m_prev = node->m_prev;
	if (node == m_head)
		m_head = node->m_next;
	if (node == m_tail)
		m_tail = node->m_prev;

	delete node;
	node = nullptr;
	return true;
}

template <class T>
bool DoublyLinkedList<T>::remove(const Node<T>* seek)
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
		node->m_prev->m_next = node->m_next;
	if (node->m_next)
		node->m_next->m_prev = node->m_prev;
	if (node == m_head)
		m_head = node->m_next;
	if (node == m_tail)
		m_tail = node->m_prev;

	delete node;
	node = nullptr;
	return true;
}

template <class T>
const T& DoublyLinkedList<T>::front() const
{
	try {
		if (!m_head)
			throw std::bad_alloc();
	}
	catch (...) {
		std::cerr << "Fatal error: Trying to read uninitialized doubly linked list..." << std::endl;
		return T();
	}
	
	return m_head->m_data;
}

template <class T>
const T& DoublyLinkedList<T>::back() const
{
	try {
		if (!m_head)
			throw std::bad_alloc();
	}
	catch (...) {
		std::cerr << "Fatal error: Trying to read uninitialized doubly linked list..." << std::endl;
		return T();
	}

	return m_tail->m_data;
}

template <class T>
bool DoublyLinkedList<T>::pop_front()
{
	return remove(uint64_t(0));
}

template <class T>
const Node<T>* DoublyLinkedList<T>::head() const
{
	return m_head;
}

template <class T>
const Node<T>* DoublyLinkedList<T>::tail() const
{
	return m_tail;
}

//template <class T>
//Node<T>* DoublyLinkedList<T>::search(uint64_t index)
//{
//	if (!m_head)
//		return nullptr;
//
//	if (index >= m_max)
//		return nullptr;
//
//	Node<T>* node = m_head;
//	while (index && node->m_next)
//	{
//		--index;
//		node = node->m_next;
//	}
//
//	if (index)
//		return nullptr;
//
//	return node;
//}

//template <class T>
//uint64_t DoublyLinkedList<T>::search(const Node<T>* seek)
//{
//	if (!seek)
//		return static_cast<uint64_t>(-1);
//
//	uint64_t index = 0;
//	Node<T>* node = m_head;
//	while (node)
//	{
//		if (node == seek)
//			return index;
//		++index;
//		node = node->m_next;
//	}
//
//	return static_cast<uint64_t>(-1);
//}

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
uint64_t DoublyLinkedList<T>::size() const
{
	return m_size;
}

template <class T>
uint64_t DoublyLinkedList<T>::max() const
{
	return m_max;
}

template <class T>
std::ostream& operator<<(std::ostream& os, const DoublyLinkedList<T>& rhs)
{
	if (!rhs.m_head)
		os << "empty";
	else
	{
		Node<T>* node = rhs.m_head;
		if (node)
		{
			os << node->m_data;
			node = node->m_next;
		}
		
		while (node)
		{
			os << " " << node->m_data;
			node = node->m_next;
		}
	}

	return os;
}