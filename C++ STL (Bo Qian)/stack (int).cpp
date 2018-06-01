#include <iostream>

struct Item
{
	int data;
	Item* prev;

	Item(int data = 0);
};

class Stack
{
	Item* top;

public:
	Stack();
	~Stack();

	void push(int data);
	void pop();
	void print();
};


int main()
{
	Stack stack;

	stack.push(70);
	stack.push(387);
	stack.push(10);
	stack.push(628);
	stack.push(1);
	stack.push(49);

	std::cout << "Before:\n";
	stack.print();

	stack.pop();
	stack.pop();

	std::cout << "After:\n";
	stack.print();

	return 0;
}




Item::Item(int data)
{
	this->data = data;
	prev = nullptr;
}

Stack::Stack()
{
	top = nullptr;
}

Stack::~Stack()
{
	Item* current = top;
	Item* delItem;

	while (current != nullptr)
	{
		delItem = current;
		current = current->prev;
		delItem->prev = nullptr;
		delete delItem;
	}
}

void Stack::push(int data)
{
	if (top == nullptr)
	{
		top = new Item(data);
	}
	else
	{
		Item* newItem = new Item(data);
		newItem->prev = top;
		top = newItem;
	}
}

void Stack::pop()
{
	if (top != nullptr)
	{
		Item* item = top;
		top = top->prev;
		item->prev = nullptr;
		delete item;
	}
}

void Stack::print()
{
	Item* item = top;

	while (item != nullptr)
	{
		std::cout << item->data << std::endl;
		item = item->prev;
	}
}