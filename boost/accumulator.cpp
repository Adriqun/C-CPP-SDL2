#include <iostream>
#include <vector>
#include <algorithm>
#include "boost/accumulators/accumulators.hpp"

// # EXAMPLE 1
#include "boost/accumulators/statistics/stats.hpp"
#include "boost/accumulators/statistics/mean.hpp"
#include "boost/accumulators/statistics/moment.hpp"
#include "boost/accumulators/statistics/sum.hpp"

// # EXAMPLE 2
#include "boost/accumulators/statistics/max.hpp"
#include "boost/accumulators/statistics/min.hpp"

// # EXAMPLE 3
#include "boost/accumulators/statistics/tail.hpp"
#include "boost/bind.hpp""
#include "boost/ref.hpp"

// # EXAMPLE 5
#include "boost/accumulators/statistics/weighted_sum.hpp"

using namespace boost::accumulators;

int main()
{
	// # EXAMPLE 1
	accumulator_set<double, stats<tag::mean, tag::moment<2>, tag::sum>> acc;
	acc(1.6);
	acc(2.7);
	acc(-3.42);
	acc(4.544);
	std::cout << "Mean:   " << mean(acc) << std::endl;
	std::cout << "Moment: " << moment<2>(acc) << std::endl;
	std::cout << "Sum:    " << sum(acc) << std::endl << std::endl;



	// # EXAMPLE 2 (accumulator copies...)
	std::vector<double> data;
	data.push_back(1.6);
	data.push_back(2.7);
	data.push_back(-3.42);
	data.push_back(4.544);
	accumulator_set<double, features<tag::min, tag::max, tag::mean>> acc2;
	acc2 = std::for_each(data.begin(), data.end(), acc2);
	std::cout << "Min:    " << min(acc2) << std::endl;
	std::cout << "Max:    " << max(acc2) << std::endl << std::endl;



	// # EXAMPLE 3 (this one is better, bind and ref pass vector by reference)
	std::vector< double > data2;
	data2.push_back(1.6);
	data2.push_back(2.7);
	data2.push_back(-3.42);
	data2.push_back(4.544);
	accumulator_set< double, features< tag::tail<left> > > acc3(tag::tail<left>::cache_size = 4);
	std::for_each(data.begin(), data.end(), boost::bind<void>(boost::ref(acc3), _1));
	std::cout << "Tail (left):    " << tail(acc3) << std::endl << std::endl;



	// # EXAMPLE 4 (own extractors), 3 ways of getting value;
	accumulator_set<double, features<tag::min>> acc4;
	acc4(-1); acc4(2);
	std::cout << "Min:    " << min(acc4) << std::endl;	// 1
	std::cout << "Min:    " << extract_result<tag::min>(acc4) << std::endl;	// 2
	extractor<tag::min> mymin;	// 3
	std::cout << "Min:    " << mymin(acc4) << std::endl << std::endl; // 3



	// # EXAMPLE 5 weighted samples
	accumulator_set<int, features<tag::weighted_sum>, int> acc5;
	acc5(1, weight = 2); //   1 * 2
	acc5(2, weight = 4); //   2 * 4
	acc5(3, weight = 6); //   3 * 6
	std::cout << "Sum:    " << sum(acc5) << std::endl << std::endl;

	return 0;
}