#include <thread>
#include <mutex>
#include <queue>
#include <fstream>
#include <string>
#include <iostream>

template<typename T>
class ThreadSafeQueue
{
	mutable std::mutex mut;
	std::queue<T> data;
	std::condition_variable cond;
public:
	ThreadSafeQueue() {}
	ThreadSafeQueue(const ThreadSafeQueue &rhs)
	{
		std::lock_guard<std::mutex> lk(rhs.mut);
		data = rhs.data;
	}

	ThreadSafeQueue& operator=(const ThreadSafeQueue&) = delete;

	void push(T newValue)
	{
		std::lock_guard<std::mutex> lk(mut);
		data.push(newValue);
		cond.notify_one();
	}

	bool try_pop(T &value)
	{
		std::lock_guard<std::mutex> lk(mut);
		if (data.empty())
			return false;
		value = data.front();
		data.pop();
		return true;
	}

	std::shared_ptr<T> try_pop()
	{
		std::lock_guard<std::mutex> lk(mut);
		if (data.empty())
			return std::shared_ptr<T>();
		std::shared_ptr<T> res(std::make_shared<T>(data.front()));
		data.pop();
		return res;
	}

	void wait_and_pop(T &value)
	{
		std::unique_lock<std::mutex> lk(mut);
		cond.wait(lk, [this] { return !data.empty(); });
		value = data.front();
		data.pop();
	}

	std::shared_ptr<T> wait_and_pop()
	{
		std::unique_lock<std::mutex> lk(mut);
		cond.wait(lk, [this] { return !data.empty(); });
		std::shared_ptr<T> res(std::make_shared<T>(data.front()));
		data.pop();
		return res;
	}

	bool empty() const
	{
		std::lock_guard<std::mutex> lk(mut);
		return data.empty();
	}
};

ThreadSafeQueue<char> data;

void data_preparation_thread()
{
	std::fstream file;
	file.open("test.txt");
	if (file.is_open())
	{
		char c;
		while ((c = file.get()) != EOF)
			data.push(c);
	}
}

void data_processing_thread()
{
	while (true)
	{
		char chunk;
		data.wait_and_pop(chunk);
		// process
		std::cout << chunk;

		// last chunk?
		if (chunk == '!')
			break;
	}
}

int main()
{
	std::thread t1(data_preparation_thread);
	std::thread t2(data_processing_thread);
	t1.join();
	t2.join();
	return 0;
}