#pragma once

template <class Object>
class Stack
{
	struct Item
	{
		Object* object;
		Item* previous;

		Item();
		~Item();
	};

	int _size;
	Item* _top;

public:
	Stack();
	~Stack();

	bool empty();
	int size();
	
	void push(Object* object);
	void pop();
	Object* top();
	void swap(Stack* stack);

	// Helper
	Item* topItem();
	void print();
};