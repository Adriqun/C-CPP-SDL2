#include <iostream>
#include <string>

void* operator new(std::size_t size) throw(std::bad_alloc)
{
	while (true)
	{
		void* pMem = malloc(size); // Allocate memory
		if (pMem)
			return pMem; // Return the memory if successful

		std::new_handler handler = std::set_new_handler(0); // Get new handler.
		std::set_new_handler(handler);

		if (handler)
			(*handler)(); // Invoke new handler
		else
			throw std::bad_alloc(); // If new handler is null throw exception
		// in case of no more memory left the handler can be set as null etc.
	}
}

int main() 
{
	int* a = new int(0);

	if (a)
		delete a;
	
	return 0;
}