#include <iostream>
#include <thread>

class Task
{
public:
	void operator()() const
	{
		std::cout << "Working...\n";
	}
};

int main()
{
	// Ok
	Task task;
	std::thread t1(task);
	t1.join();
	
	// One thing to consider when passing a function object to the thread constructor is
	// to avoid what is dubbed “C++’s most vexing parse.” If you pass a temporary rather
	// than a named variable, then the syntax can be the same as that of a function declaration,
	// in which case the compiler interprets it as such, rather than an object definition.

	// Not ok
	std::thread t2(Task());
	//t2.join();
	// Declares a function t2 that takes a single parameter of type pointer to a function
	// taking no parameters and returning a Task object, like:
	extern int function(int());

	// To avoid the problem:
	// Ok
	std::thread t3((Task()));
	t3.join();

	// Ok
	std::thread t4{(Task())};
	t4.join();

	// Ok (lambda expression)
	std::thread t5([] {Task()(); });
	t5.join();

	return 0;
}