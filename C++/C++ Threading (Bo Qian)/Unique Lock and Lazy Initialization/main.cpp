#include <thread>
#include <fstream>
#include <string>
#include <mutex>

class LogFile
{
	std::mutex m_mutex;
	std::ofstream m_ofstream;
	std::once_flag m_flag;
public:
	void print(std::string msg, int i)
	{	// this will open file once by only one thread
		std::call_once(m_flag, [&]() { m_ofstream.open("log.txt"); });

		std::unique_lock<std::mutex> locker(m_mutex, std::defer_lock);
		locker.lock();
		if (m_ofstream.is_open())
			m_ofstream << "id: " << i << " " << msg << std::endl;
		// some funtionality...
		locker.unlock();
	}
};


void function(LogFile& log)
{
	for (int i = 0; i > -100; i--)
		log.print(std::string("From another thread: "), i);
}

int main()
{
	LogFile log;
	std::thread thread(function, std::ref(log));

	for (int i = 0; i < 100; i++)
		log.print(std::string("From main thread: "), i);

	thread.join();
	return 0;
}