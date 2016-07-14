#include <iostream>
#include <cstdlib>

using namespace std;

int main()
{
    int t;
    cin >> t;
    while( t-- )
    {
        int a,b;
        cin >> a >> b;

        if( abs( a ) == abs( b ) )
            cout << 0 << endl;
        else
        {
            if( a%b == 0 )
            {
                cout << 0 << endl;
                continue;
            }

            int result = a / b;

            if( a < 0 )
            {
                if( b > 0 ) result--;
                else        result++;
            }

            cout << a - result * b << endl;
        }
    }

    return 0;
}
