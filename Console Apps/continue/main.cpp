#include <iostream>

using namespace std;

int main()
{
    for( int16_t i = 0; i < 10; i++ )
    {
        cout << "Before number: " << i << endl;

        if( i % 2 == 0 )
            continue;

        cout << "After nr: " << i << endl;
    }

    return 0;
}
