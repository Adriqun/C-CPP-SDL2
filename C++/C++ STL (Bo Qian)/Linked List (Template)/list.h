#pragma once

template<class Object>
class List
{
	struct Node
	{
		Object* object;
		Node* next;

		Node();
		~Node();
	};

	int _size;
	Node* head;

public:
	List();
	~List();
	void free();

	void add(Object* object);
	bool remove(Object* object);

	void print();
	int size();
	bool empty();
};