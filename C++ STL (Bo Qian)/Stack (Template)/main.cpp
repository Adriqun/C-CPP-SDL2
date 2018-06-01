#include "myInt.h"
#include "stack.h"



int main()
{
	Stack <MyInt>* stack;
	stack = new Stack <MyInt>;

	stack->push(new MyInt(1));
	stack->push(new MyInt(67));
	stack->push(new MyInt(823));
	stack->push(new MyInt(94));
	stack->push(new MyInt(5));

	std::cout << "BEFORE\n";
	stack->print();
	std::cout << std::endl;

	stack->pop();
	stack->pop();

	std::cout << "AFTER\n";
	stack->print();

	delete stack;
	stack = nullptr;

	return 0;
}