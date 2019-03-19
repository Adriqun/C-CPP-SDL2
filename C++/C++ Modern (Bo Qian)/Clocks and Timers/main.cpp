#include <iostream>
#include <chrono>

// Example 1
/*
Clock: (represent by ratios)
std::chrono::system_clock: current time according to the system "if 2 hours passed it is not sure if 2 hours passed"
std::chrony::steady_clock: goes at a uniform rate "if 2 hours passed it must have been 2 hours"
std::chrono::high_resolution_clock: provides smallest possible tick period.

Duration:
std::chrono::duration<>:
2 hours (a number and a unit)
duration<int, ratio<1, 1>> // number of seconds stored in int
duration<double, ratio<60, 1>> // number of minutes stored in double
nanoseconds, microseconds, miliseconds, seconds, minutes, hours
system_clock::duration - duration<T, system_clock::period>
*/
/*int main()
{
	//std::ratio<1, 10> r; // 2/10 -> 1/5
	//std::cout << r.num << "/" << r.den << std::endl;
	//std::cout << std::chrono::system_clock::period::num << "/" << std::chrono::system_clock::period::den << std::endl;
	
	std::chrono::microseconds mi(2700); // 2700
	mi.count(); // gives 2700
	std::chrono::nanoseconds na = mi; // 2700000
	na.count(); // gives 2700000
	std::chrono::milliseconds mili = std::chrono::duration_cast<std::chrono::milliseconds>(mi); // 2
	mi = mili + mi; // no cast needed


	return 0;
}*/

// Example 2
// Time Point
/*
	std::chrono::time_point<>: represents a point of time
	00:00 January 1, 1970 (Coordinated Universal Time - UTC) - epoch of a clock
	time_point<system_clock, miliseconds>: according to the system clock the elapsed time since epoch in miliseconds
	system_clock::time_point - time_point<system_clock, system_clock::duration>
	steady_clock::time_point - time_point<steady_clock, steady_clock::duration>
*/
int main()
{
	std::chrono::system_clock::time_point tp = std::chrono::system_clock::now(); // current time of system_clock
	std::cout << tp.time_since_epoch().count() << std::endl;
	tp += std::chrono::seconds(2);
	std::cout << tp.time_since_epoch().count() << std::endl;

	// measure time
	std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
	std::cout << "i am bored\n";
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	std::chrono::steady_clock::duration dur = end - start;
	// if (dur == 0) // <- wrong
	if (dur == std::chrono::steady_clock::duration::zero())
		std::cout << "no time elapsed\n";
	std::cout << std::chrono::duration_cast<std::chrono::microseconds>(dur).count() << std::endl;
	return 0;
}