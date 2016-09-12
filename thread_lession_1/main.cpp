#include <iostream>
#include <thread>

void function()
{
	std::cout << "Beaty is only skin-deep" << std::endl;
}

int main(int argc, char **argv)
{
    std::thread t1( function );	// t1 starts running
	// t1.join();	// main thread waits for t1 to finish
	t1.detach(); 	// t1 will freely on its own -- daemon process
	
	if( t1.joinable() )
		t1.join();
	
    return 0;
}
