#include <thread>
#include <vector>
#include <algorithm>
#include <functional>

void some_function();
void some_other_function(int);

std::thread f()
{
	return std::thread(some_function); // Implicitly returing object with std::move(...).
}

std::thread g()
{
	std::thread t(some_other_function, 42);
	return t; // Implicitly returing object with std::move(...).
}

void h(std::thread t)
{

}

void i()
{	// Spawning threads
	std::vector<std::thread> threads;
	for (unsigned i = 0; i < 20; ++i)
		threads.push_back(std::thread(some_function, i));

	std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
}

int main()
{
	// std::thread is movable but not copyable!
	std::thread t(some_function);
	//h(t); // Won't compile
	h(std::move(t)); // Ok

	i();
	return 0;
}