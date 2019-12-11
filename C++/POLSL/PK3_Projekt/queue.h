/*
	File: queue.h
	Author: Adrian Michalek
	Github: https://github.com/devmichalek
	Classes:
		Queue - implementation of queue of type T
	Example of Queue<int> (front is on the left):
		Insert 1			| Queue: 1
		Insert 2			| Queue: 1 2
		Insert 3			| Queue: 1 2 3
		Insert 4			| Queue: 1 3 4 4
		Remove				| Queue: 2 3 4
		Remove				| Queue: 3 4
		Remove				| Queue: 4
*/

#pragma once
#include "doublylinkedlist.h"

template<class T>
class Queue
{
	static unsigned int m_count; // Represents number of instantiated objects
	DoublyLinkedList<T> m_data;

public:
	Queue(); // Default constructor
	Queue(const Queue<T>&); // Copy constructor (reference)
	Queue(const Queue<T>&&); // Copy constructor (move semantics)
	~Queue(); // Destructor
	bool insert(T); // Inserts new element
	bool remove(); // Removes element from the front
	unsigned int size();
	const T& top();
	const unsigned int& count();

	// Overloaded operators:
	Queue<T>& operator=(const Queue&);
	Queue<T>& operator=(const Queue&&);
	Queue<T>& operator+=(const Queue&);
	Queue<T>& operator+=(const Queue&&);
	Queue<T>& operator-=(const Queue&);
	Queue<T>& operator-=(const Queue&&);
	friend std::ostream& operator<<(std::ostream& os, const Queue&);
};

template<class T>
unsigned int Queue<T>::m_count = 0;

template<class T>
Queue<T>::Queue()
{
	++m_count;
}

template<class T>
Queue<T>::Queue(const Queue<T>& rhs)
{
	m_data = rhs.m_data;
}

template<class T>
Queue<T>::Queue(const Queue<T>&& rhs)
{
	m_data = rhs.m_data;
}

template<class T>
Queue<T>::~Queue()
{
	--m_count;
}

template<class T>
bool Queue<T>::insert(T element)
{
	return m_data.insert(element);
}

template<class T>
bool Queue<T>::remove()
{
	return m_data.pop_front();
}

template<class T>
unsigned int Queue<T>::size()
{
	return m_data.size();
}

template<class T>
const T& Queue<T>::top()
{
	return m_data.front();
}

template<class T>
const unsigned int& Queue<T>::count()
{
	return m_count;
}

template<class T>
Queue<T>& Queue<T>::operator=(const Queue& rhs)
{
	m_data = rhs.m_data;
	return *this;
}

template<class T>
Queue<T>& Queue<T>::operator=(const Queue&& rhs)
{
	m_data = rhs.m_data;
	return *this;
}

template<class T>
Queue<T>& Queue<T>::operator+=(const Queue& rhs)
{
	m_data += rhs.m_data;
	return *this;
}

template<class T>
Queue<T>& Queue<T>::operator+=(const Queue&& rhs)
{
	m_data += rhs.m_data;
	return *this;
}

template<class T>
Queue<T>& Queue<T>::operator-=(const Queue& rhs)
{
	m_data -= rhs.m_data;
	return *this;
}

template<class T>
Queue<T>& Queue<T>::operator-=(const Queue&& rhs)
{
	m_data -= rhs.m_data;
	return *this;
}

template<class T>
std::ostream& operator<<(std::ostream& os, const Queue<T>& rhs)
{
	os << rhs.m_data;
}