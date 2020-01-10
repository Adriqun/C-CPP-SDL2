#include <future>
#include <thread>
#include <iostream>
#include <deque>

int factorial(int n)
{
	int res = 1;
	for (int i = n; i > 1; --i)
		res *= i;
	std::cout << res << std::endl;
	return res;
}

std::deque<std::packaged_task<int(int)>> tasks;
std::mutex mutex;
std::condition_variable condition;

void thread_1()
{
	std::packaged_task<int(int)> t;
	{
		std::unique_lock<std::mutex> locker(mutex);
		condition.wait(locker, []() { return !tasks.empty(); });
		t = std::move(tasks.front());
		tasks.pop_front();
	}
	t(5);
}

int main()
{
	std::thread t1(thread_1);
	std::packaged_task<int(int)> t(factorial); // Packaged task links callable object with the future!
	std::future<int> fu = t.get_future();
	{
		std::lock_guard<std::mutex> locker(mutex);
		tasks.push_back(t);
	}
	condition.notify_one();
	std::cout << fu.get();
	t1.join();

	return;
}