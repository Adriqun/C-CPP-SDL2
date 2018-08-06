#include <iostream>
#include <vector>
#include <algorithm>
#include "boost/scope_exit.hpp"

void function()
{
	int* pointer = nullptr;
	pointer = new int[99];

	// RAII, you are always sure that array is deallocated
	BOOST_SCOPE_EXIT(pointer)
	{
		delete[] pointer;
		pointer = nullptr;
	} BOOST_SCOPE_EXIT_END

	return;
}

int main()
{
	function();

	return 0;
}