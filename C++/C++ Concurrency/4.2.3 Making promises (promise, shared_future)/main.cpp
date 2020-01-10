#include <future>
#include <thread>
#include <iostream>
#include <vector>
#include <chrono>
#include <assert.h>

std::mutex mutex_cout;
void shared_cout(std::string msg);

int main()
{
	// std::future is protected with locks so only one thread can use the get() function.
	// On the other hand std::shared_future is not protected with locks, data race is possible.
	// Copying the std::shared_future is safe.

	// Example of creating shared future from future
	{
		std::promise<int> promise;
		std::future<int> future(promise.get_future());
		assert(future.valid());
		std::shared_future<int> sf(std::move(future));
		assert(!future.valid());
		assert(sf.valid());
	}
	// Another example
	{
		std::promise<int> promise;
		std::shared_future<int> sf(promise.get_future());
	}
	// Another example
	{
		std::promise<int> promise;
		auto sf = promise.get_future().share();
	}

	// Example with std::promise, std::shared_future
	{
		std::string f0(std::shared_future<int> future);
		std::string f1(std::shared_future<int> future);
		std::string f2(std::shared_future<int> future);
		std::string f3(std::shared_future<int> future);

		// Create promise and shared future
		std::promise<int> promise;
		std::shared_future<int> sf(promise.get_future());

		// Run threads async. / Pair of future and status (true = value already retrieved)
		std::vector<std::pair<std::future<std::string>, bool>> futures;
		futures.push_back(std::make_pair(std::async(std::launch::async, f0, sf), false));
		futures.push_back(std::make_pair(std::async(std::launch::async, f1, sf), false));
		futures.push_back(std::make_pair(std::async(std::launch::async, f2, sf), false));
		futures.push_back(std::make_pair(std::async(std::launch::async, f3, sf), false));

		// For now I don't have data for future...
		// Doing some work...
		shared_cout("Main thread: working...");
		std::this_thread::sleep_for(std::chrono::milliseconds(1500));
		shared_cout("Main thread: done...");

		// Got data, send data to other threads
		promise.set_value(147);

		std::string result;
		bool got_all_results = false;
		while (!got_all_results)
		{
			got_all_results = true;
			for (auto &i : futures)
				if (!i.second)
				{
					switch (i.first.wait_for(std::chrono::milliseconds(10)))
					{
						case std::future_status::deferred:
						case std::future_status::timeout:
							got_all_results = false;
							break;
						case std::future_status::ready:
							// Value is ready from particular thread!
							if (!result.empty())
								result += ", ";
							result += i.first.get();
							i.second = true; // Set that value was retrieved
							break;
					}
				}

		}

		shared_cout("Main thread: Got values in order: " + result);
	}

	return 0;
}

void shared_cout(std::string msg)
{
	std::lock_guard<std::mutex> locker(mutex_cout);
	std::cout << msg << std::endl;
}

std::string f0(std::shared_future<int> future)
{
	shared_cout("f0: Hello!");
	std::this_thread::sleep_for(std::chrono::milliseconds(350));
	shared_cout("f0: Done some work, waiting for value...");
	int data = future.get(); // Wait for value then set data
	shared_cout("f0: Got value!");

	std::this_thread::sleep_for(std::chrono::milliseconds(4000));
	shared_cout("f0: Returning value!");
	return "f0";
}

std::string f1(std::shared_future<int> future)
{
	shared_cout("f1: Hello!");
	std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	shared_cout("f1: Done some work, waiting for value...");
	int data = future.get(); // Wait for value then set data
	shared_cout("f1: Got value!");

	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	shared_cout("f1: Returning value!");
	return "f1";
}

std::string f2(std::shared_future<int> future)
{
	shared_cout("f2: Hello!");
	std::chrono::steady_clock::time_point tp = std::chrono::steady_clock::now() + std::chrono::microseconds(25000);
	std::this_thread::sleep_until(tp);
	shared_cout("f2: Done some work, waiting for value...");
	int data = future.get(); // Wait for value then set data
	shared_cout("f2: Got value!");

	std::this_thread::sleep_for(std::chrono::microseconds(1000));
	shared_cout("f2: Returning value!");
	return "f2";
}

std::string f3(std::shared_future<int> future)
{
	shared_cout("f3: Hello!");
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	shared_cout("f3: Done some work, waiting for value...");
	int data = future.get(); // Wait for value then set data
	shared_cout("f3: Got value!");

	std::chrono::steady_clock::time_point tp = std::chrono::steady_clock::now() + std::chrono::milliseconds(4000);
	std::this_thread::sleep_until(tp);
	shared_cout("f3: Returning value!");
	return "f3";
}