#include <stdio.h>
#include <thread>

void function()
{
	printf( "Beaty is only skin-deep\n" );
}

int main(int argc, char **argv)
{
	std::thread t1( function ); // t1 starts running
	// t1.join(); // main thread waits for t1 to finish
	t1.detach(); // t1 will freely on its own -- deamon process
	
	//...
	
	if( t1.joinable() )
		t1.join();
	
	return 0;
}
