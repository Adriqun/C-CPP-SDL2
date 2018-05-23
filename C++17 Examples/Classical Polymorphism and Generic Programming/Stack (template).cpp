#include <iostream>
#include <string>

using namespace std;

template <class Type>
class Stack {
	int sizeData;
	int realSize;
	Type* data;
	Type topData;

public:
	Stack();
	~Stack();
	bool empty();
	void pop();
	void push(Type data);
	int size();
	void swap(Stack& stack);
	Type top();
};

template <class Type>
Stack<Type>::Stack() {
	sizeData = 0;
	realSize = 0;
	data = nullptr;
	topData = -1;
}

template <class Type>
Stack<Type>::~Stack() {
	sizeData = 0;
	realSize = 0;
	if (data != nullptr) {
		delete data;
		data = nullptr
	}
}

template <class Type>
bool Stack<Type>::empty() {
	return sizeData == 0;
}

template <class Type>
void Stack<Type>::pop() {
	if (sizeData > 0)
	{
		--sizeData;
		sizeData > 0 ? topData = data[sizeData - 1] : topData = 0;
	}
}

template <class Type>
void Stack<Type>::push(Type data) {
	// First time
	if (this->data == nullptr) {
		realSize = 2;
		this->data = new Type[realSize];
		this->data[sizeData] = data;
	}
	else if (sizeData < realSize) {
		this->data[sizeData] = data;
	}
	else {
		Type* temp = new Type[realSize];
		for (int i = 0; i < realSize; ++i) {
			temp[i] = this->data[i];
		}

		delete this->data;
		realSize *= 2;
		this->data = new Type[realSize];
		for (int i = 0; i < sizeData; ++i) {
			this->data[i] = temp[i];
		}
		this->data[sizeData] = data;
	}

	++sizeData;
	topData = data;
}

template <class Type>
int Stack<Type>::size() {
	return sizeData;
}

template <class Type>
void Stack<Type>::swap(Stack& stack) {

}

template <class Type>
Type Stack<Type>::top() {
	if (sizeData > 0) {
		return topData;
	}

	throw "Stack is empty!";
}

int main()
{
	Stack <int>* stack = new Stack<int>;

	stack->push(15);
	stack->push(11);
	stack->push(23);
	stack->push(45);

	while (stack->size() > 0) {
		cout << stack->top() << ", ";
		stack->pop();
	}

	return 0;
}