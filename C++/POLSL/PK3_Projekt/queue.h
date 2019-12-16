/*
	File: queue.h
	Author: Adrian Michalek
	Github: https://github.com/devmichalek/Tutorials/tree/master/C%2B%2B/POLSL/PK3_Projekt
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

enum class QueueState : unsigned int
{
	EMPTY = 0,	// Queue is empty (0 elements)
	FULL,		// Queue is full (max elements)
	FILLED		// Queue is filled (at least 1 element)
};

enum QueueOperation : unsigned int
{
	NO_ERROR = 0,
	REMOVE_EMPTY,
	INSERT_OVERFLOW,
	CLEAR_EMPTY
};

template<class T>
class Queue
{
	static unsigned int m_count; // Represents number of instantiated objects
	DoublyLinkedList<T> m_data;
	QueueOperation m_error;

public:
	Queue(); // Default constructor
	Queue(const Queue<T>&); // Copy constructor (reference)
	Queue(const Queue<T>&&); // Copy constructor (move semantics)
	~Queue(); // Destructor
	bool insert(const T&); // Inserts new element (reference)
	bool insert(const T&&); // Inserts new element (move semantics)
	bool remove(); // Removes element from the front
	uint64_t size() const; // Returns current number of elements
	const T& front(); // Returns first element
	const T& back(); // Returns last element
	QueueState state() const; // Returns current state of the queue
	const QueueOperation& error() const; // Returns last error state of the queue
	static const unsigned int& count(); // Returns current number of instantiated objects
	bool clear(); // Removes all the data from the queue

	// Overloaded operators:
	Queue<T>& operator=(const Queue&);
	Queue<T>& operator=(const Queue&&);
	Queue<T>& operator+=(const Queue&);
	Queue<T>& operator+=(const Queue&&);
	template<class U>
	friend std::ostream& operator<<(std::ostream& os, const Queue<U>&);
};

template<class T>
unsigned int Queue<T>::m_count = 0;

template<class T>
Queue<T>::Queue()
{
	++m_count;
	m_error = QueueOperation::NO_ERROR;
}

template<class T>
Queue<T>::Queue(const Queue<T>& rhs)
{
	m_data = rhs.m_data;
	m_error = QueueOperation::NO_ERROR;
}

template<class T>
Queue<T>::Queue(const Queue<T>&& rhs)
{
	m_data = rhs.m_data;
	m_error = QueueOperation::NO_ERROR;
}

template<class T>
Queue<T>::~Queue()
{
	--m_count;
}

template<class T>
bool Queue<T>::insert(const T &element)
{
	if (!m_data.insert(element))
	{
		m_error = QueueOperation::INSERT_OVERFLOW;
		return false;
	}

	return true;
}

template<class T>
bool Queue<T>::insert(const T&& element)
{
	if (!m_data.insert(element))
	{
		m_error = QueueOperation::INSERT_OVERFLOW;
		return false;
	}

	return true;
}

template<class T>
bool Queue<T>::remove()
{
	if (!m_data.pop_front())
	{
		m_error = QueueOperation::REMOVE_EMPTY;
		return false;
	}

	return true;
}

template<class T>
uint64_t Queue<T>::size() const
{
	return m_data.size();
}

template<class T>
const T& Queue<T>::front()
{
	return m_data.front();
}

template<class T>
const T& Queue<T>::back()
{
	return m_data.back();
}

template<class T>
QueueState Queue<T>::state() const
{
	if (!size())
		return QueueState::EMPTY;
	if (m_data.size() == m_data.max())
		return QueueState::FULL;
	return QueueState::FILLED;
}

template<class T>
const QueueOperation& Queue<T>::error() const
{
	return m_error;
}

template<class T>
const unsigned int& Queue<T>::count()
{
	return m_count;
}

template<class T>
bool Queue<T>::clear()
{
	if (!m_data.clear())
	{
		m_error = QueueOperation::CLEAR_EMPTY;
		return false;
	}

	m_error = QueueOperation::NO_ERROR;
	return true;
}

template<class T>
Queue<T>& Queue<T>::operator=(const Queue<T>& rhs)
{
	m_data = rhs.m_data;
	return *this;
}

template<class T>
Queue<T>& Queue<T>::operator=(const Queue<T>&& rhs)
{
	m_data = rhs.m_data;
	return *this;
}

template<class T>
Queue<T>& Queue<T>::operator+=(const Queue<T>& rhs)
{
	m_data += rhs.m_data;
	return *this;
}

template<class T>
Queue<T>& Queue<T>::operator+=(const Queue<T>&& rhs)
{
	m_data += rhs.m_data;
	return *this;
}

template<class T>
std::ostream& operator<<(std::ostream& os, const Queue<T>& rhs)
{
	switch (rhs.state())
	{
		case QueueState::EMPTY:
			os << "Queue (empty) <= ";
			return os;
		case QueueState::FULL:
			os << "Queue (full) <= ";
			break;
		case QueueState::FILLED:
			os << "Queue (filled) <= ";
			break;
	}

	os << rhs.m_data;
	return os;
}