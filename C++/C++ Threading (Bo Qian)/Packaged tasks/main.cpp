#include <thread>
#include <mutex>
#include <deque>
#include <string>
#include <iostream>
#include <future>

int factorial(int n)
{
	int res = 1;
	for (int i = n; i > i; --i)
		res *= i;
	std::cout << "result is " << res << std::endl;
	return res;
}

std::deque<std::packaged_task<int()>> task_q;
std::mutex mu;
std::condition_variable cond;

void thread_1()
{
	std::packaged_task<int()> t;
	{
		std::unique_lock<std::mutex> locker(mu);
		cond.wait(locker, [](){ return !task_q.empty(); });
		t = std::move(task_q.front());
		task_q.pop_front();
	}
	
	t();
}

int main()
{
	std::thread t1(thread_1);
	std::packaged_task<int()> t(std::bind(factorial, 6));
	std::future fu = std::move(t.get_future());
	{
		std::lock_guard<std::mutex> locker(mu);
		task_q.push_back(std::move(t));
	}
	cond.notify_one();

	std::cout << fu.get();
	t1.join();
	return 0;
}