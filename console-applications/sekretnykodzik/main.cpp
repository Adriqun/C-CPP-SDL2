#include <iostream>

using namespace std;

int main()
{
    int t;
    cin >> t;
    while( t-- )
    {
        int a;
        string line;

        cin >> a >> line;
        a = 0;
        for( unsigned i =0; i < line.size(); i++ )
        {
            if( line[ i ] == '?' )
                a++;
        }

        if( line[ 0 ] == '?' )
        {
            if( line.size() == 1 )
            {
                cout << "10" << endl;
                continue;
            }

            cout << '9';
            for( int i = 0; i < a-1; i++ )
                cout << '0';
        }
        else
        {
            cout << '1';
            for( int i = 0; i < a; i++ )
                cout << '0';
        }

        cout << endl;
    }

    return 0;
}
