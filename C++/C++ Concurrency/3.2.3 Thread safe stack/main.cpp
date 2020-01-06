#include <exception>
#include <memory>
#include <mutex>
#include <stack>

struct empty_stack : std::exception
{
	const char* what() const throw();
};

template<typename T>
class ThreadSafeStack
{
	std::stack<T> data;
	mutable std::mutex mutex;

public:
	ThreadSafeStack()
	{
	}

	ThreadSafeStack(const ThreadSafeStack& other)
	{
		std::lock_guard<std::mutex> lock(other.mutex);
		data = other.data;
	}

	ThreadSafeStack& operator=(const ThreadSafeStack&) = delete;

	void push(T new_value)
	{
		std::lock_guard<std::mutex> lock(mutex);
		data.push(new_value);
	}

	std::shared_ptr<T> pop()
	{
		std::lock_guard<std::mutex> lock(mutex);
		if (data.empty())
			throw empty_stack();
		std::shared_ptr<T> const res(std::make_shared<T>(data.top()));
		data.pop();
		return res;
	}

	void pop(T& value)
	{
		std::lock_guard<std::mutex> lock(mutex);
		if (data.empty())
			throw empty_stack();
		value = data.top();
		data.pop();
	}

	bool empty() const
	{
		std::lock_guard<std::mutex> lock(mutex);
		return data.empty();
	}
};

int main()
{
	return 0;
}