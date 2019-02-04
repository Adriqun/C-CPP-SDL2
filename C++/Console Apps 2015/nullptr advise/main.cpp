#include <iostream>

using namespace std;

void func( int n )
{
    cout << "It's int" << endl;
}

void func( string s )
{
    cout << "It's string" << endl;
}



int main()
{
    // func( 0 );
    // func( "s" );
    func( NULL ); // guess which function gets called?

    return 0;
}
