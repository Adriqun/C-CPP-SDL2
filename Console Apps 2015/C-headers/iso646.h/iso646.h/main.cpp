#include <iso646.h>
#include <iostream>

int main( )
{
    using namespace std;
    int a = 3, b = 2, result;

    result = a &= b; // and_eq
    cout << result << endl;

    if( true ^ false ) // xor
    {
        cout << "True value - xor" << endl;
    }

    unsigned bitmask;
    bitmask = ~ 0xF107;
}
