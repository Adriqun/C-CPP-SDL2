#include <iostream>
#include <cmath>

using namespace std;

string intToStr( int n )
{
    string tmp;
    if(n < 0)
    {
        tmp = "-";
        n = -n;
    }
    if( n > 9 )
        tmp += intToStr(n / 10);
    tmp += n % 10 + 48;
    return tmp;
}

int main()
{
    // zerujemy tablice
    int nr = 21;
    int tab[ nr ];
    for( int i = 0; i < nr; i++ )
        tab[ i ] = 0;


    // wczytujemy liczby
    int n;
    while( cin >> n )
        tab[ n+10 ]++;


    // szukamy najwiekszej
    float m = 0;
    for( int i = 0; i < nr; i++ )
        if( tab[ i ] > m )
            m = tab[ i ];


    const int MAX = 30;

    // wypisywanie
    for( int i = 0; i < nr; i++ )
    {

        // spacje jesli to konieczne
        string line = intToStr( i-10 );
        for( unsigned k = 0; k < 4 - line.size(); k++ )
            cout << ' ';

        cout << i-10 << ":|";

        int ile = round( MAX * tab[ i ] / m );

        for( int k = 1; k <= MAX; k++ )
        {
            if( k <= ile )
                cout << '*';
            else
               cout << ' ';
        }

        cout << "|\n";
    }

    return 0;
}
