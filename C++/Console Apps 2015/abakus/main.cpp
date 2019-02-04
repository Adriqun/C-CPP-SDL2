#include <iostream>

using namespace std;

/*
    Najwiekszy problem w tym zadaniu stanowily zera wiodace,
    poczatkowo myslalem ze problem tkwi w wyswietlaniu znakow,
    okazalo sie ze wspisywana zmienna nalezy traktowac jak liczbe!
    czyli 00025 = 25, 205 = 205, 000 = 0, 0 = 0, 01 = 1 itd.
    Komentarz z 2016-06-20 Adrian Michalek klasa II Slaskie Techniczne
    Zaklady Naukowe.
*/

string abakus;

string typ[ 10 ]= { "** -    *****",
                    "** -*    ****",
                    "** -**    ***",
                    "** -***    **",
                    "** -****    *",
                    "* *-    *****",
                    "* *-*    ****",
                    "* *-**    ***",
                    "* *-***    **",
                    "* *-****    *" };

void wypisuje()
{
    if( abakus.size() > 1 )
    {
        string newabakus = "";
        for( unsigned i = 0; i < abakus.size(); i++ )
        {
            if( abakus[ i ] != '0' )
            {
                for( unsigned j = i; j < abakus.size(); j++ )
                {
                    newabakus += abakus[ j ];
                }
                break;
            }
        }

        abakus = newabakus;
    }

    for( unsigned i = 0; i < abakus.size() + 2; i ++ )
    {
        cout << '-';
    }

    for( int j = 0; j <= 12; j ++ )
    {
        cout << endl << '|';
        for( unsigned i = 0; i < abakus.size(); i ++ )
        {
            int znak = static_cast<int>( abakus[ i ] ) -48;
            cout << typ[ znak ][ j ];
        }
        cout << '|';
    }

    cout << endl;

    for( unsigned i = 0; i < abakus.size() + 2; i ++ )
    {
        cout << '-';
    }

    cout << endl;
}

void wczytuje()
{
    string line = "";
    for( int i = 0; i <= 15; i ++ )
    {
        getline( cin, abakus );
        line += abakus;
    }

    int len = abakus.size();

    string result;
    for( int i = 1; i < len-1; i ++ )
    {
        string which = "";
        for( int j = 1; j < 14; j ++ )
        {
            which += line[ j * len + i ];
        }

        for( int i = 0; i < 10; i ++ )
        {
            if( which == typ[ i ] )
            {
                char znak = static_cast<char>( i + 48 );
                result += znak;
            }
        }
    }

    string newresult = "";
    for( unsigned i = 0; i < result.size(); i++ )
    {
        if( result[ i ] != '0' )
        {
            for( unsigned j = i; j < result.size(); j++ )
            {
                newresult += result[ j ];
            }
            cout << newresult << endl;
            break;
        }
        else if( i == result.size() - 1 )
        {
            cout << "0" << endl;
            break;
        }
    }
}

int main()
{
    int n;
    while( cin >> n )
    {
        if( n == 1 )
        {
            cin >> abakus;
            wypisuje();
        }
        else
        {
            wczytuje();
        }
    }

    return 0;
}
