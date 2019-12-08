#pragma once

template<class T>
class DoublyLinkedList
{
	struct Node
	{
		T m_data;
		Node<T>* m_prev;
		Node<T>* m_next;

		Node(T data, const Node* prev = nullptr, const Node* next = nullptr)
		{
			m_data = data;
			m_prev = prev;
			m_next = next;
		}

		explicit Node<T> operator=(Node<T>&& x)
		{
			m_data = x.m_data;
			m_prev = x.m_prev;
			m_next = x.m_next;
		}
	};

	Node* m_head;
	Node* m_tail;
	__int64 m_size;

public:
	explicit DoublyLinkedList();
	explicit DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>&);
	explicit DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>&&);
	void add(const T&);
	void add(const T&&);
	void add(T);
	void remove();
	void clear();
	__int64 size();
	DoublyLinkedList<T> operator++();		// pre
	DoublyLinkedList<T> operator++(int);	// post
};


template<class T>
DoublyLinkedList<T>::DoublyLinkedList()
{
	m_size = 0;
	m_head = nullptr;
	m_tail = nullptr;
}

template<class T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>& x)
{
	clear();
	m_size = x.m_size;
	m_head = x.m_head;
	m_tail = x.m_tail;
}

template<class T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>&& x)
{
	clear();
	m_size = x.m_size;
	m_head = x.m_head;
	m_tail = x.m_tail;
}

template <class T>
void DoublyLinkedList<T>::add(const T& data)
{
	Node* newNode = new Node();
}

template <class T>
void DoublyLinkedList<T>::add(const T&& data)
{

}

template <class T>
void DoublyLinkedList<T>::add(T data)
{

}

template <class T>
void DoublyLinkedList<T>::remove()
{

}

template <class T>
void DoublyLinkedList<T>::clear()
{
	m_size = 0;

}

template <class T>
__int64 DoublyLinkedList<T>::size()
{
	return m_size;
}

template <class T>
DoublyLinkedList<T> DoublyLinkedList<T>::operator++()
{

}

template <class T>
DoublyLinkedList<T> DoublyLinkedList<T>::operator++(int)
{

}