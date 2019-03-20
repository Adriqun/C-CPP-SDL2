#include <iostream>
#include <random>
#include <chrono>
#include <vector>
#include <string>

int main()
{
	unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
	std::default_random_engine e(seed);
	std::cout << e() << std::endl;

	// Range: [0, 5)
	std::cout << e() % 6 << std::endl;
	// 1. Bad quality of randomness
	// 2. Can only provide uniform distribution

	std::uniform_int_distribution<int> distr(0, 5); // range : [0, 5]
	std::cout << distr(e) << std::endl;

	std::uniform_int_distribution<int> distrR(0, 5); // range : [0, 5)
	std::cout << distrR(e) << std::endl;

	std::poisson_distribution<int> distrP(1.0); // mean
	std::cout << distrP(e) << std::endl;

	std::normal_distribution<double> distrN(10.0, 5.0); // mean and standard deviation
	std::vector<int> v(20);
	for (int i = 0; i < 800; ++i)
	{
		int num = distrN(e); // convert double to int
		if (num >= 0 && num < 20)
			++v[num];
	}

	for (int i = 0; i < v.size(); ++i)
		std::cout << std::string(v[i], '.') << std::endl;;

	return 0;
}