#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int nr = 100;
    vector <int> array( 100 );

    for( int i = 0; i < nr; i++ )
    {
        array[ i ] = i;
    }

    for( vector <int> ::iterator it = array.begin(); it != array.end(); it++ )
    {
        cout << *it;
    }

    return 0;
}
