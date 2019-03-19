#include <iostream>
#include <sstream>
#include <random>
#include <chrono>
#include <vector>

int main()
{
	std::default_random_engine engine;
	std::cout << "Min: " << engine.min() << std::endl;
	std::cout << "Max: " << engine.max() << std::endl;

	std::cout << engine() << std::endl;
	std::cout << engine() << std::endl;

	// ---- STATE ----
	std::stringstream state;
	state << engine; // save the current state

	std::cout << engine() << std::endl;
	std::cout << engine() << std::endl;

	state >> engine; // restore the state

	std::cout << engine() << std::endl;
	std::cout << engine() << std::endl;
	// ---- STATE ----

	// changing state while creating engine
	// engine2 and engine3 are different
	unsigned seed2 = std::chrono::steady_clock::now().time_since_epoch().count();
	std::default_random_engine engine2(seed2);
	unsigned seed3 = std::chrono::steady_clock::now().time_since_epoch().count();
	std::default_random_engine engine3(seed3);
	std::cout << engine2() << std::endl;
	std::cout << engine3() << std::endl;

	engine2.seed(); // reset engine to initial state
	engine2.seed(1009); // set engine state to 1009
	engine3.seed(1009);
	if (engine2 == engine3)
		std::cout << "engine2 and engine3 have the same state\n";

	// shuffle vector or deck
	std::vector<int> vec = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	std::shuffle(vec.begin(), vec.end(), std::default_random_engine());

	return 0;
}