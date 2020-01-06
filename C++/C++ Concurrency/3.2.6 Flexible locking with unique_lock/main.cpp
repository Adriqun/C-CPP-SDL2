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
			return;

		// Example with std::unique_lock where locking is deffered.
		std::unique_lock<std::mutex> lock_a(lhs.m, std::defer_lock);
		std::unique_lock<std::mutex> lock_b(rhs.m, std::defer_lock);

		// Mutexes are locked here:
		std::lock(lock_a, lock_b);
		swap(lhs.knight, rhs.knight);
	}
};

int main()
{
	return 0;
}