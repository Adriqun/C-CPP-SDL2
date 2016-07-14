#include <iostream>

using namespace std;

string intToStr( int n )
{
    string tmp;

    if( n < 0 )
    {
        tmp = "-";
        n = -n;
    }
    if( n > 9 )
        tmp += intToStr( n / 10 );
    tmp += n % 10 + 48;

    return tmp;
}

void sumUp()
{
    // zawsze one jest liczba dluzsza
    string one, two;

    cin >> one >> two;

    if( one.size() < two.size() )
    {
        string buf;
        buf = one;
        one = two;
        two = buf;
    }

    int buf = 0; /* przechowuje chwilowe dodawanie */
    string result = "", temp = "";
    int i = one.size()-1, j = two.size()-1;

    int a, b;

    for( ;; )
    {
        a = static_cast<int>(one[ i ]) - 48;
        if( j < 0 ) b = 0;
        else        b = static_cast<int>(two[ j ]) - 48;

        buf += a + b;

        if( buf > 9 )
        {
            temp = intToStr( buf );
            result += temp[ 1 ];
            buf = static_cast<int>(temp[ 0 ]) - 48;
        }
        else
        {
            result += static_cast<char>( buf + 48 );
            buf = 0;
        }

        if( i == 0 )
        {
            result += static_cast<char>( buf + 48 );
            break;
        }

        j--;
        i--;
    }

    string newresult = "";
    for( int i = result.size()-1; i >= 0; i-- )
    {
        if( result[ i ] != '0' )
        {
            for( int j = i; j >= 0; j-- )
                newresult += result[ j ];
            break;
        }

        if( i == 0 )
        {
            newresult += result[ 0 ];
        }
    }

    cout << newresult << endl;
}

int main()
{
    int t;
    cin >> t;
    while( t-- )
    {
        sumUp();
    }
    return 0;
}
