#include <thread>

class ThreadGuard
{
	std::thread& thread;

public:
	explicit ThreadGuard(std::thread& t) :
		thread(t)
	{
	
	}

	~ThreadGuard()
	{
		if (thread.joinable())
		{
			thread.join();
		}
	}

	ThreadGuard(ThreadGuard const&) = delete;
	ThreadGuard& operator=(ThreadGuard const&) = delete;
};

void do_something()
{

}

struct Struct
{
	Struct(int x) {}
};

void function()
{
	int state = 0;
	Struct str(state);
	std::thread thread(str);
	ThreadGuard guard(thread);
	do_something(); // Even if function throws an exception the thread will join at destruction of guard.
}

int main()
{
	function();
	return 0;
}