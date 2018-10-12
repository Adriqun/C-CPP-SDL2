#include <boost/algorithm/searching/boyer_moore.hpp>
#include <boost/algorithm/searching/boyer_moore_horspool.hpp>
#include <boost/algorithm/searching/knuth_morris_pratt.hpp>

#include <string>
#include <vector>
#include <iostream>

#include <cstdlib>
#include <ctime>

// Comparison beetween 3 algorithms

/*
About Booyer Moore Horspool Algorithm

The Boyer-Moore-Horspool search algorithm was published by Nigel Horspool in 1980. 
It is a refinement of the Boyer-Moore algorithm that trades space for time. 
It uses less space for internal tables than Boyer-Moore, and has poorer worst-case performance.
*/

/*
About Knuth Morris Pratt Algotihm

It does this by building a table from the pattern being searched for, 
with one entry for each element in the pattern.
The algorithm was conceived in 1974 by Donald Knuth and Vaughan Pratt, 
and independently by James H. Morris. The three published it jointly in 
1977 in the SIAM Journal on Computing http://citeseer.ist.psu.edu/context/23820/0
*/

void printElapsedTime(const char* info, clock_t b, clock_t e)
{
	std::cout << info << ", elapsed time: " << double(e - b) / CLOCKS_PER_SEC << std::endl;
}

int main()
{
	srand(time(nullptr));
	const int length = 10000000;
	clock_t beginTime, endTime;

	std::string pattern = "1532486970";
	std::string corpus = "";

	// Fill corpus.
	for (int i = 0; i < length / 2; ++i)
		corpus += std::to_string(rand() % 10 + 1);
	corpus += pattern;
	for (int i = 0; i < length / 2; ++i)
		corpus += std::to_string(rand() % 10 + 1);

	// Boyer Moore
	beginTime = clock();
	auto it = boost::algorithm::boyer_moore_search(corpus.begin(), corpus.end(), pattern.begin(), pattern.end());
	endTime = clock();
	printElapsedTime("Boyer Moore", beginTime, endTime);

	// Boyer Moore Horspool
	beginTime = clock();
	auto jt = boost::algorithm::boyer_moore_search(corpus.begin(), corpus.end(), pattern.begin(), pattern.end());
	endTime = clock();
	printElapsedTime("Boyer Moore Horspool", beginTime, endTime);

	// Knuth Morris Pratt
	beginTime = clock();
	auto kt = boost::algorithm::boyer_moore_search(corpus.begin(), corpus.end(), pattern.begin(), pattern.end());
	endTime = clock();
	printElapsedTime("Knuth Morris Pratt", beginTime, endTime);

	size_t pos_i = corpus.end() - it.first;
	size_t pos_j = corpus.end() - jt.first;
	size_t pos_k = corpus.end() - kt.first;

	return 0;
}
