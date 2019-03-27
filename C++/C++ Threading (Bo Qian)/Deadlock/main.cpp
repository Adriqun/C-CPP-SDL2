#include <thread>
#include <iostream>
#include <string>
#include <mutex>

class LogFile
{
	std::mutex m_mutex;
	std::mutex m_mutex2;

public:
	/* Deadlock
	void shared_print(std::string id, int value)
	{
		std::lock_guard <std::mutex> locker(m_mutex);
		std::lock_guard <std::mutex> locker2(m_mutex2);
		std::cout << "From " << id << ": " << value << std::endl;
	}

	void shared_print2(std::string id, int value)
	{
		std::lock_guard <std::mutex> locker2(m_mutex2);
		std::lock_guard <std::mutex> locker(m_mutex);
		std::cout << "From " << id << ": " << value << std::endl;
	}
	*/
	// Solution 1 -> correct order of mutexes
	/*void shared_print(std::string id, int value)
	{
		std::lock_guard <std::mutex> locker(m_mutex);
		std::lock_guard <std::mutex> locker2(m_mutex2);
		std::cout << "From " << id << ": " << value << std::endl;
	}

	void shared_print2(std::string id, int value)
	{
		std::lock_guard <std::mutex> locker(m_mutex);
		std::lock_guard <std::mutex> locker2(m_mutex2);
		std::cout << "From " << id << ": " << value << std::endl;
	}*/
	// Solution 2 -> using std::lock and std::adopt_lock
	void shared_print(std::string id, int value)
	{
		std::lock(m_mutex, m_mutex2);
		std::lock_guard <std::mutex> locker(m_mutex, std::adopt_lock);
		std::lock_guard <std::mutex> locker2(m_mutex2, std::adopt_lock);
		std::cout << "From " << id << ": " << value << std::endl;
	}

	void shared_print2(std::string id, int value)
	{
		std::lock(m_mutex, m_mutex2);
		std::lock_guard <std::mutex> locker2(m_mutex2, std::adopt_lock);
		std::lock_guard <std::mutex> locker(m_mutex, std::adopt_lock);
		std::cout << "From " << id << ": " << value << std::endl;
	}
};


void function(LogFile& log)
{
	for (int i = 0; i > -100; i--)
	{
		log.shared_print(std::string("From t1: "), i);
	}
}

int main()
{
	LogFile log;
	std::thread t1(function, std::ref(log));

	for (int i = 0; i < 100; i++)
	{
		log.shared_print2(std::string("From main: "), i);
	}

	t1.join();

	return 0;
}