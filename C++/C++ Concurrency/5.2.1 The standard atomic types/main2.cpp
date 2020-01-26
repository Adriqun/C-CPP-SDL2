#include <atomic>
#include <thread>
#include <vector>
#include <iostream>
#include <string>

/*
This type is a really simple Boolean flag, and operations on this type
are required to be lock-free; once you have a simple lock-free Boolean flag, you can use
that to implement a simple lock and thus implement all the other atomic types using that
as a basis
*/
std::atomic_flag lock = ATOMIC_FLAG_INIT;
void f(int n)
{
	for (int cnt = 0; cnt < 5; ++cnt) {
		while (lock.test_and_set(std::memory_order_acquire))
			;
		std::cout << "Output from thread " << std::this_thread::get_id() << ": " << n << '\n';
		lock.clear(std::memory_order_release); // Release lock
	}
}

int main()
{
	struct TooComplex
	{
		int table[100];
	};

	struct Simple
	{
		int a, b;
	};

	// is_lock_free:
	// true - operations on this type will require less CPU instructions
	// false - operations on this type will require the use of a mutex

	std::atomic<TooComplex> complex;
	std::atomic<Simple> simple;
	std::cout << complex.is_lock_free() << std::endl;	// false
	std::cout << simple.is_lock_free() << std::endl;	// true
	std::cout << std::atomic_is_lock_free(&complex) << std::endl;	// false
	std::cout << std::atomic_is_lock_free(&simple) << std::endl;	// true
	std::cout << std::atomic<TooComplex>::is_always_lock_free << std::endl;	// false
	std::cout << std::atomic<Simple>::is_always_lock_free << std::endl;		// true

	std::vector<std::thread> v;
	for (int n = 0; n < 4; ++n)
		v.emplace_back(f, n);

	for (auto& t : v)
		t.join();

	return 0;
}
