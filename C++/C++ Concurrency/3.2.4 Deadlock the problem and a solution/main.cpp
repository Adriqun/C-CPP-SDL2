#include <thread>
#include <mutex>

struct Knight
{
	int x;
};

void swap(Knight& lhs, Knight& rhs)
{
	int x = lhs.x;
	lhs.x = rhs.x;
	rhs.x = x;
}

class X
{
private:
	Knight knight;
	std::mutex m;
public:
	X(Knight const& sd) : knight(sd)
	{
	}

	friend void swap(X& lhs, X& rhs)
	{
		if (&lhs == &rhs)
			return; // Check if lhs and rhs are different instances

		// Avoid deadlock by using std::lock
		std::lock(lhs.m, rhs.m);

		std::lock_guard<std::mutex> lock_a(lhs.m, std::adopt_lock);
		std::lock_guard<std::mutex> lock_b(rhs.m, std::adopt_lock);
		// The std::adopt_lock parameter is supplied in addition to the mutex
		// to indicate to the std::lock_guard objects that the mutexes
		// are already locked, and they should just adopt the ownership of the existing lock on
		// the mutex rather than attempt to lock the mutex in the constructor.

		swap(lhs.knight, rhs.knight);
	}
};

int main()
{
	// Tips:
	// 1. Avoid nested locks.
	// 2. Avoid calling user-supplied code while holding a lock.
	// 3. Acquire locks in a fixed order.
	// 4. Use a lock hierarchy
	return 0;
}