#include <future>
#include <thread>
#include <iostream>

template<typename T>
std::list<T> sequential_quick_sort(std::list<T> input)
{
	if (input.empty())
		return input;

	std::list<T> result;
	result.splice(result.begin(), input, input.begin());
	T const& pivot = *result.begin();

	auto divide_point = std::partition(input.begin(), input.end(), [&](T const& t) { return t < pivot; });

	std::list<T> lower_part;
	lower_part.splice(lower_part.end(), input, input.begin(), divide_point);
	auto new_lower(sequential_quick_sort(std::move(lower_part)));
	auto new_higher(sequential_quick_sort(std::move(input)));

	result.splice(result.end(), new_higher);
	result.splice(result.begin(), new_lower);
	return result;
}

// naive algorithm
template<typename T>
std::list<T> parallel_quick_sort(std::list<T> input)
{
	if (input.empty())
		return input;

	std::list<T> result;
	result.splice(result.begin(), input, input.begin());
	T const& pivot = *result.begin();

	auto divide_point = std::partition(input.begin(), input.end(), [&](T const& t) { return t < pivot; });

	std::list<T> lower_part;
	lower_part.splice(lower_part.end(), input, input.begin(), divide_point);
	std::future<std::list<T> > new_lower(std::async(&parallel_quick_sort<T>, std::move(lower_part)));
	auto new_higher(parallel_quick_sort(std::move(input)));

	result.splice(result.end(), new_higher);
	result.splice(result.begin(), new_lower.get());
	return result;
}

template<class F, class A>
std::future<typename std::result_of<F(A&&)>::type> spawn_task(F&& f, A&& a)
{
	typedef std::result_of<F(A&&)>::type result_type;
	std::packaged_task<result_type(A&&)> task(std::move(f)));
	std::future<result_type> result(task.get_future());
	std::thread thread(std::move(task), std::move(a));
	thread.detach();
	return result;
}

int main()
{

	return 0;
}
