#include <boost/algorithm/searching/boyer_moore.hpp>
#include <string>
#include <vector>
/*
Overview copied from boost site.

The Boyer–Moore string search algorithm is a particularly efficient string searching algorithm, 
and it has been the standard benchmark for the practical string search literature. The Boyer-Moore 
algorithm was invented by Bob Boyer and J. Strother Moore, and published in the October 1977 issue 
of the Communications of the ACM , and a copy of that article is available at 
http://www.cs.utexas.edu/~moore/publications/fstrpos.pdf.
*/

// As far as I know it is preferable to use object type if you are going to use thi algorithm multiple times.
// Procedural type is preferable for quick rare actions that can take during programm execution - A. M. 2018

/*
The Boyer - Moore search algorithm uses two tables, a "bad character" table
to tell how far to skip ahead when it hits a character that is not in the pattern,
and a "good character" table to tell how far to skip ahead when it hits a
mismatch on a character that _is_ in the pattern.
*/

int main()
{
	// procedural
	std::string corpus = "Hello Boyer Moore";
	std::string pattern = "yer";
	
	size_t pos;
	auto it = boost::algorithm::boyer_moore_search(corpus.begin(), corpus.end(), pattern.begin(), pattern.end());
	if (it.first != corpus.end())
	{
		pos = corpus.end() - it.first;
		printf("Found at position %d\n", pos);
	}

	// objective
	std::vector<int> cor = { 1, 2, 3, 3, 2, 2, 1, 3, 1, 3 };
	std::vector<int> pat = { 3, 2 };

	boost::algorithm::boyer_moore<std::vector<int>::iterator> seeker(pat.begin(), pat.end());
	auto jt = seeker(cor.begin(), cor.end());

	if (jt.first != cor.end())
	{
		pos = cor.size() - (cor.end() - jt.first);
		printf("Pattern found at %d\n", pos);
	}

	return 0;
}
