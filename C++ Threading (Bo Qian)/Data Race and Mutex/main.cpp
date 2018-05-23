#include <stdio.h>
#include <thread>
#include <iostream>
#include <mutex>
#include <fstream>

class LogFile
{
	std::mutex m_mutex;
	std::ofstream f;
	
public:
	
	LogFile()
	{
		f.open( "log.txt" );
	}
	
	void shared_print( std::string id, int value )
	{
		std::lock_guard <std::mutex> guard( m_mutex ); // RAII
		f << "From " << id << ": " << value << std::endl;
	}
	
	// Never return f to the outside world
	// ofstream& getStream() { return f; )
	// Never pass f an argument to user provided function
	// void processf( void fun( ofstream& ) ) { fun( f ) }
	
};




void function( LogFile& log )
{
	for( int i = 0; i > -100; i-- )
	{
		log.shared_print( std::string( "From t1: " ), i );
	}
}

int main()
{
	LogFile log;
	std::thread t1( function, std::ref( log ) );
	
	for( int i = 0; i < 100; i ++ )
	{
		log.shared_print( std::string( "From main: " ), i );
	}
	
	t1.join();
	
	return 0;
}