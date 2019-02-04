#include "stack.h"
#include "myInt.h"

template <class Object>
Stack<Object>::Item::Item()
{
	object = nullptr;
	previous = nullptr;
}

template <class Object>
Stack<Object>::Item::~Item()
{
	if (object != nullptr)
	{
		delete object;
		object = nullptr;
	}
}

template <class Object>
Stack<Object>::Stack()
{
	_size = 0;
	_top = nullptr;
}

template <class Object>
Stack<Object>::~Stack()
{
	Item* current = _top;
	Item* delItem;

	while (current != nullptr)
	{
		delItem = current;
		current = current->previous;
		delItem->previous = nullptr;
		delete delItem;
	}

	_size = 0;
}

template <class Object>
bool Stack<Object>::empty()
{
	return _top == nullptr;
}

template <class Object>
int Stack<Object>::size()
{
	return _size;
}

template <class Object>
void Stack<Object>::push(Object* object)
{
	++_size;
	Item* newItem = new Item();
	newItem->object = object;

	if (empty())
	{
		_top = newItem;
	}
	else
	{
		newItem->previous = _top;
		_top = newItem;
	}
}

template <class Object>
void Stack<Object>::pop()
{
	if (!empty())
	{
		--_size;
		Item* delItem = _top;
		_top = _top->previous;
		delItem->previous = nullptr;
		delete delItem;
	}
}

template <class Object>
Object* Stack<Object>::top()
{
	return _top->object;
}

template <class Object>
void Stack<Object>::swap(Stack* stack)
{
	Item* i1 = _top;
	Item* i2 = stack->topItem();

	_top = stack->topItem();
	i2 = i1;
}

template <class Object>
typename Stack<Object>::Item* Stack<Object>::topItem()
{
	return _top;
}

template <class Object>
void Stack<Object>::print()
{
	Item* current = _top;
	while (current != nullptr)
	{
		std::cout << current->object;
		current = current->previous;
	}
}

template class Stack <int>;
template class Stack <MyInt>;