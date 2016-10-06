#include <iostream>
#include <thread>

using namespace std;

class Fctor
{
public:
	
	void operator()( string msg )
	{
		cout << "thread says: " << msg << endl;
	}
};

int main(int argc, char **argv)
{
	// Oversuubscription is bad 
	cout << std::thread::hardware_concurrency() << endl; // Indication
	
	
	string s = "Where there is no trust, there is no love";
	
	cout << std::this_thread::get_id() << endl;	// main thread
	
	thread t1( ( Fctor() ), std::move( s ) ); // t1 starts running
	// using RAII
	// Wrapper w( t1 );
	
	cout << t1.get_id() << endl;
	
	std::thread t2 = std::move( t1 );

	t2.join();
	
	// cout << "From main: " << s << endl;
	
	return 0;
}
