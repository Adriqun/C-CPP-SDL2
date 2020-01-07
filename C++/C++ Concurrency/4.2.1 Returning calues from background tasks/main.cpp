#include <future>
#include <string>
#include <iostream>

int some_work()
{
	return 0xff;
}

void f()
{
	std::future<int> answer = std::async(some_work);
	//...
	std::cout << "Answer is: " << answer.get() << std::endl;
}

struct X
{
	void foo(int i, const std::string& str) { std::cout << "i:" << i << " str:" << str << std::endl; }
	std::string bar(std::string const& str) { std::cout << str; return str; }
};

struct Y
{
	double operator()(double d) { std::cout << d << "\n" << std::flush; return d; }
};

X baz(X& x)
{
	std::cout << "baz\n";
	return x;
}

class MoveOnly
{
public:
	MoveOnly() {}
	MoveOnly(MoveOnly&&) {}
	MoveOnly(MoveOnly const&) = delete;
	MoveOnly& operator=(MoveOnly&&) {}
	MoveOnly& operator=(MoveOnly&) = delete;
	void operator()() {}
};

int main()
{
	// You use std::async to start an asynchronous task for which you don’t need the
	// result right away.
	f();

	X x;
	auto f1 = std::async(&X::foo, &x, 42, "Hello");
	auto f2 = std::async(&X::bar, &x, "Goodbye");
	auto f3 = std::async(Y(), 2.34);
	auto f4 = std::async(baz, std::ref(x));
	auto f5 = std::async(MoveOnly());
	auto f6 = std::async(std::launch::async, Y(), 1.2);
	auto f7 = std::async(std::launch::deferred, baz, std::ref(x));
	auto f8 = std::async(std::launch::deferred | std::launch::async, baz, std::ref(x));
	auto f9 = std::async(baz, std::ref(x));
	f7.wait(); // Invoke deffered function.

	return 0;
}