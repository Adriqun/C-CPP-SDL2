#include <atomic>
#include <thread>
#include <vector>
#include <future>
#include <mutex>
#include <iostream>
#include <string>

class TaskManager
{
	unsigned int m_taskCounter;
	std::atomic<unsigned int> m_activeTaskCounter;
	const unsigned int m_maxNumberOfActiveTasks;
	
	std::mutex mutex;
	std::vector<std::packaged_task<void(char*)>> m_tasks;
	std::vector<std::pair<std::future<void>, bool>> m_results;

	void RunTaskInternal(unsigned int index, char* data)
	{
		if (m_activeTaskCounter < m_maxNumberOfActiveTasks)
		{
			std::lock_guard<std::mutex> locker(mutex);
			if (!m_results[index].second)
			{
				++m_activeTaskCounter;
				std::thread(std::move(m_tasks[index]), data).detach();
			}
		}
	}

	unsigned int AddTaskSignatureInternal(void(*function)(char*))
	{
		std::lock_guard<std::mutex> locker(mutex);
		m_tasks.emplace_back(function);
		m_results.push_back(std::make_pair(m_tasks.back().get_future(), false));
		m_taskCounter++;
		return m_results.size() - 1;
	}

	void RemoveTaskSignatureInternal(unsigned int index)
	{
		std::lock_guard<std::mutex> locker(mutex);
		m_results[index].second = true;
		--m_activeTaskCounter;
	}

	void Sweep()
	{
		if (m_activeTaskCounter == 0)
		{
			std::lock_guard<std::mutex> locker(mutex);
			bool done = true;
			for (unsigned int i = 0; i < m_results.size(); ++i)
			{
				if (!m_results[i].second)
				{
					done = false;
					break;
				}
			}

			if (done)
			{
				m_tasks.clear();
				m_results.clear();
			}
		}
	}

public:
	TaskManager() : m_maxNumberOfActiveTasks(8)
	{
		m_taskCounter = 0;
		m_activeTaskCounter.store(0);
	}

	unsigned int AddTaskSignature(void(*function)(char*))
	{
		return AddTaskSignatureInternal(function);
	}
	
	bool RunTaskByIndex(unsigned int index, char* data)
	{
		if (index >= m_tasks.size())
			return false;
		RunTaskInternal(index, data);
		return true;
	}

	void LoopMe()
	{
		for (unsigned int i = 0; i < m_results.size(); ++i)
		{
			switch (m_results[i].first.wait_for(std::chrono::milliseconds(10)))
			{
				case std::future_status::deferred:
				case std::future_status::timeout:
					break;
				case std::future_status::ready:
					// Value is ready from particular thread!
					RemoveTaskSignatureInternal(i);
					break;
			}
		}

		Sweep();
	}
};

int main()
{
	void add(char*);
	void substract(char*);
	void multiply(char*);
	void Print(std::string);

	TaskManager tm;
	bool active = true;
	bool running = false;
	char choice = '\0';
	while (active)
	{
		std::cin >> choice;
		switch (choice)
		{
			case 'r':
			{
				running = !running;
				if (running)
					Print("Main: State changed to running state...");
				else
					Print("Main: State changed to adding state...");
				break;
			}
			case 'a':
			{
				if (!running)
				{
					unsigned int index = tm.AddTaskSignature(add);
					Print("Main: Added new task signature of function \"add\", index is " + std::to_string(index));
					break;
				}

				unsigned int index;
				struct AddStruct { int a, b; }; AddStruct addStruct;
				std::cin >> index >> addStruct.a >> addStruct.b;
				if (tm.RunTaskByIndex(index, reinterpret_cast<char*>(&addStruct)))
					Print("Main: Run new task \"add\".");
				else
					Print("Main: Could not find function index " + std::to_string(index));
				break;
			}
			case 's':
			{
				if (!running)
				{
					unsigned int index = tm.AddTaskSignature(substract);
					Print("Main: Added new task signature of function \"substract\", index is " + std::to_string(index));
					break;
				}

				unsigned int index;
				struct SubstractStruct { double a, b; }; SubstractStruct substractStruct;
				std::cin >> index >> substractStruct.a >> substractStruct.b;
				if (tm.RunTaskByIndex(index, reinterpret_cast<char*>(&substractStruct)))
					Print("Main: Run new task \"substract\".");
				else
					Print("Main: Could not find function index " + std::to_string(index));
				break;
			}
			case 'm':
			{
				if (!running)
				{
					unsigned int index = tm.AddTaskSignature(multiply);
					Print("Main: Added new task signature of function \"multiply\", index is " + std::to_string(index));
					break;
				}

				unsigned int index;
				struct MultiplyStruct { unsigned int a, b; }; MultiplyStruct multiplyStruct;
				std::cin >> index >> multiplyStruct.a >> multiplyStruct.b;
				if (tm.RunTaskByIndex(index, reinterpret_cast<char*>(&multiplyStruct)))
					Print("Main: Run new task \"multiply\".");
				else
					Print("Main: Could not find function index " + std::to_string(index));
				break;
			}
			default:
			{
				Print("Could not find expected program option...");
				break;
			}
		}

		tm.LoopMe();
	}

	return 0;
}

std::mutex mutex;
void Print(std::string message)
{
	std::lock_guard<std::mutex> locker(mutex);
	std::cout << message << std::endl;
}

void add(char* args)
{
	Print("Started \"add\" function...");
	std::this_thread::sleep_for(std::chrono::milliseconds(1100));
	int a = *reinterpret_cast<int*>(args);
	int b = *reinterpret_cast<int*>(args + 4);
	int result = a + b;
	std::this_thread::sleep_for(std::chrono::milliseconds(1200));
	Print("Computed \"add\" function...");
	Print("\"add\" function returned " + std::to_string(result));
}

void substract(char* args)
{
	Print("Started \"substract\" function...");
	std::this_thread::sleep_for(std::chrono::milliseconds(650));
	double a = *reinterpret_cast<double*>(args);
	double b = *reinterpret_cast<double*>(args + 8);
	double result = a - b;
	std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	Print("Computed \"substract\" function...");
	Print("\"substract\" function returned " + std::to_string(result));
}

void multiply(char* args)
{
	Print("Started \"multiply\" function...");
	std::this_thread::sleep_for(std::chrono::milliseconds(1500));
	unsigned int a = *reinterpret_cast<unsigned int*>(args);
	unsigned int b = *reinterpret_cast<unsigned int*>(args + 4);
	unsigned int result = a * b;
	std::this_thread::sleep_for(std::chrono::milliseconds(750));
	Print("Computed \"multiply\" function...");
	Print("\"multiply\" function returned " + std::to_string(result));
}