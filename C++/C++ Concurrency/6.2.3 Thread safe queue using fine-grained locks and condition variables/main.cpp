#include <memory>
#include <mutex>
#include <condition_variable>

template<typename T>
class ThreadSafeQueue
{
	struct Node
	{
		std::shared_ptr<T> m_data;
		std::unique_ptr<Node> m_next;
	};

	std::mutex m_headMutex;
	std::mutex m_tailMutex;
	std::unique_ptr<Node> m_head;
	Node* m_tail;
	std::condition_variable m_condition;

	Node* get_tail()
	{
		std::lock_guard<std::mutex> tailLocker(m_tailMutex);
		return m_tail;
	}

	std::unique_ptr<Node> pop_head()
	{
		std::unique_ptr<Node> oldHead = std::move(m_head);
		m_head = std::move(oldHead->m_next);
		return oldHead;
	}

	std::unique_lock<std::mutex> wait_for_data()
	{
		std::unique_lock<std::mutex> headLocker(m_headMutex);
		m_condition.wait(headLocker, [&] { return m_head.get() != get_tail(); });
		return std::move(headLocker);
	}

	std::unique_ptr<Node> wait_pop_head()
	{
		std::unique_lock<std::mutex> headLocker(wait_for_data());
		return pop_head();
	}

	std::unique_ptr<Node> wait_pop_head(T& value)
	{
		std::unique_lock<std::mutex> headLocker(wait_for_data());
		value = std::move(*m_head->m_data);
		return pop_head();
	}

	std::unique_ptr<Node> try_pop_head()
	{
		std::lock_guard<std::mutex> headLocker(m_headMutex);
		if (m_head.get() == get_tail())
			return std::unique_ptr<Node>(); // Queue is empty
		return pop_head();
	}

	std::unique_ptr<Node> try_pop_head(T& value)
	{
		std::lock_guard<std::mutex> headLocker(m_headMutex);
		if (m_head.get() == get_tail())
			return std::unique_ptr<Node>(); // Queue is empty
		value = std::move(*m_head->m_data);
		return pop_head();
	}

public:
	ThreadSafeQueue() : m_head(new Node), m_tail(m_head.get())
	{
	}

	ThreadSafeQueue(const ThreadSafeQueue&) = delete;
	ThreadSafeQueue& operator=(const ThreadSafeQueue&) = delete;

	std::shared_ptr<T> try_pop()
	{
		std::unique_ptr<Node> oldHead = try_pop_head();
		return oldHead ? oldHead->m_data : std::shared_ptr<T>();
	}

	bool try_pop(T& value)
	{
		std::unique_ptr<Node> const oldHead = try_pop_head();
		return oldHead;
	}

	std::shared_ptr<T> wait_and_pop()
	{
		std::unique_ptr<Node> const oldHead = wait_pop_head();
		return oldHead->m_data;
	}

	void wait_and_pop(T& value)
	{
		std::unique_ptr<Node> const oldHead = wait_pop_head(value);
	}

	void push(T newValue)
	{
		std::shared_ptr<T> newData(std::make_shared<T>(std::move(newValue)));
		std::unique_ptr<Node> newPtr(new Node);
		
		{
			std::lock_guard<std::mutex> tailLocker(m_tailMutex);
			m_tail->m_data = newData;
			Node* const newTail = newPtr.get();
			m_tail->m_next = std::move(newPtr);
			m_tail = newTail;
		}

		m_condition.notify_one();
	}

	bool empty()
	{
		std::lock_guard<std::mutex> headLocker(m_headMutex);
		return m_head.get() == get_tail();
	}
};

int main()
{
	ThreadSafeQueue<unsigned int> queue;
	queue.try_pop();
	queue.push(static_cast<unsigned int>(-1));
	queue.empty();
	queue.wait_and_pop();
	return 0;
}