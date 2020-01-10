#include <future>
#include <thread>
#include <iostream>
#include <chrono>

std::mutex mutex_cout;
void shared_cout(std::string msg)
{
	std::lock_guard<std::mutex> locker(mutex_cout);
	std::cout << msg << std::endl;
}

std::string f(std::shared_future<int> future)
{
	shared_cout("Hello!");
	std::this_thread::sleep_for(std::chrono::milliseconds(300));
	shared_cout("Done some work, waiting for value...");
	int data = future.get(); // Wait for value then set data
	shared_cout("Got value!");

	std::this_thread::sleep_for(std::chrono::milliseconds(250));
	shared_cout("Returning value!");
	return "Returned value";
}

int main()
{
	// Create promise
	std::promise<int> promise;

	// Run thread async.
	auto future = std::async(std::launch::async, f, promise.get_future().share());

	// For now I don't have data for future...
	// Doing some work...
	shared_cout("Main thread: working...");
	std::this_thread::sleep_for(std::chrono::milliseconds(1500));
	shared_cout("Main thread: done...");

	bool status = true;
	try
	{
		std::string s;
		s.resize(std::numeric_limits<int>::max());
	}
	catch (...)
	{
		// Ups.. I don't have data, I broke promise...
		status = false;
		promise.set_exception(std::current_exception());
		// Another option is std::copy_exception...
	}

	if (status)
	{
		// Wair for value and print it
		std::cout << future.get() << std::endl;
	}

	return 0;
}
