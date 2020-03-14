#include <memory>
#include <mutex>
#include <iostream>

template<typename T>
class ThreadSafeList
{
	struct Node
	{
		std::mutex m_mutex;
		std::shared_ptr<T> m_data;
		std::unique_ptr<Node> m_next;

		Node() : m_next()
		{
		}

		Node(T const& value) : m_data(std::make_shared<T>(value))
		{
		}
	};

	Node m_head;

public:
	ThreadSafeList()
	{
	}

	ThreadSafeList(ThreadSafeList const&) = delete;
	ThreadSafeList& operator=(ThreadSafeList const&) = delete;

	void push_front(T const& value)
	{
		std::unique_ptr<Node> newNode(new Node(value));
		std::lock_guard<std::mutex> locker(m_head.m_mutex);
		newNode->m_next = std::move(m_head.m_next);
		m_head.m_next = std::move(newNode);
	}

	template<typename Function>
	void for_each(Function function)
	{
		Node* current = &m_head;
		std::unique_lock<std::mutex> lk(m_head.m_mutex);
		while (Node* const next = current->m_next.get())
		{
			std::unique_lock<std::mutex> next_lk(next->m_mutex);
			lk.unlock();
			function(*next->m_data);
			current = next;
			lk = std::move(next_lk);
		}
	}

	template<typename Predicate>
	std::shared_ptr<T> find_first_if(Predicate predicate)
	{
		Node* current = &m_head;
		std::unique_lock<std::mutex> lk(m_head.m_mutex);
		while (Node* const next = current->m_next.get())
		{
			std::unique_lock<std::mutex> next_lk(next->m_mutex);
			if (predicate(*next->m_data))
				return next->m_data;
			current = next;
			lk = std::move(next_lk);
		}

		return std::shared_ptr<T>();
	}

	template<typename Predicate>
	void remove_if(Predicate predicate)
	{
		Node* current = &m_head;
		std::unique_lock<std::mutex> lk(m_head.m_mutex);
		while (Node* const next = current->m_next.get())
		{
			std::unique_lock<std::mutex> next_lk(next->m_mutex);
			if (predicate(*next->m_data))
			{
				std::unique_ptr<Node> oldNext = std::move(current->m_next);
				current->m_next = std::move(next->m_next);
				next_lk.unlock();
			}
			else
			{
				lk.unlock();
				current = next;
				lk = std::move(next_lk);
			}
		}
	}
};

int main()
{
	ThreadSafeList<char> tsl;
	tsl.push_front('a');
	tsl.push_front('b');
	tsl.push_front('c');
	tsl.push_front('d');
	tsl.for_each([](char& i) { std::cout << i << ' '; });
	std::cout << std::endl;

	tsl.remove_if([](char& i) { return i == 'b'; });
	tsl.for_each([](char& i) { std::cout << i << ' '; });
	std::cout << std::endl;

	std::shared_ptr<char> result = tsl.find_first_if([](char& i) { return i == 'a'; });
	std::cout << "a = " << *result << std::endl;
	return 0;
}