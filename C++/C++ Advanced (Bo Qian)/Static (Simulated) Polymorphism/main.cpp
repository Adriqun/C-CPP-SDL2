#include <iostream>
#include <string>

struct Node
{
	int data;
	Node* next;
};

void process_node(Node* node, std::string msg)
{
	if (!node)
		node = new Node;
	
	std::cout << msg << std::endl;
}

// Dynamic Polymorphism
class Person
{
public:
	void parse(Node* node)
	{
		process(node);
	}

	virtual void process(Node* node) = 0;
};

class Worker : public Person
{
public:
	void process(Node* node)
	{
		process_node(node, "Dynamic Polymorphism");
	}
};

// Static Polymorphism, Simulated Polymorphism
template <typename T> class GenericPerson
{
public:
	void parse(Node* node)
	{
		process(node);
	}

	void process(Node* node)
	{
		static_cast<T*>(this)->process(node);
	}
};

class GenericWorker : public GenericPerson<GenericWorker>
{
public:
	void process(Node* node)
	{
		process_node(node, "Static Polymorphism");
	}
};

// Pros and cons of static polymorphism
// 1. No (pure) virtual functions.
// 2. Some functions are called by themself
// 3. Curiously reccuring template pattern
// 4. No dynamic binding (less cost of compilation, virtual table)
// 5. All of the dispatching can be determined at compile time instead of at runtime.
// 6. Performance is better but program image size is worse.
// 7. No pointer to base class.

// Cost of virtual functions in dynamic polymorphism
// Calling a virtual function is slower than calling a non-virtual function for a couple of reasons:
// First, we have to use the *__vptr to get to the appropriate virtual table.
// Second, we have to index the virtual table to find the correct function to call.
// Only then can we call the function. As a result, we have to do 3 operations to find the function to call,
// as opposed to 2 operations for a normal indirect function call, or one operation for a direct function call.
// However, with modern computers, this added time is usually fairly insignificant.


int main() 
{
	Node* root = nullptr;
	Worker worker;
	GenericWorker gWorker;
	worker.process(root);
	gWorker.process(root);
	return 0;
}