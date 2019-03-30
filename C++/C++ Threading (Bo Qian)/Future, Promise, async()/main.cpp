#include <future>
#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include <string>
using namespace std;

mutex global_mutex;

void myprint(string msg, int i)
{
	unique_lock<mutex> locker(global_mutex, std::defer_lock);
	locker.lock();
	cout << msg << " " << i << endl;
	locker.unlock();
}

int factorial(shared_future<int> /*&*/f)
{
	int res = 1;
	int n = f.get();
	for (int i = n; i > 1; --i)
		res *= i;
	myprint("result is:", res);
	return res;
}

int main()
{
	int x;
	promise<int> pp;
	promise<int> p = std::move(pp);
	future<int> f = p.get_future();
	shared_future<int> sf = f.share();

	future<int> fu = std::async(std::launch::async, factorial, sf);
	future<int> fu2 = std::async(std::launch::async, factorial, sf);
	future<int> fu3 = std::async(std::launch::async, factorial, sf);
	// ... 10 threads
	myprint("middle:", 0);
	
	// do something else
	// ...
	this_thread::sleep_for(chrono::milliseconds(20));
	// in case if we broken promise, if promise cannot be set we have to add line below
	//p.set_exception(make_exception_ptr(runtime_error("broken promise")));
	p.set_value(4);

	x = fu.get();
	myprint("x is:", x);
	return 0;
}