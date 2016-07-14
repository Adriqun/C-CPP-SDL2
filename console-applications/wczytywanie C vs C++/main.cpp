#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cstdio>
#include <ctime>

using namespace std;

void loading_one()
{
    string line;
    fstream file;

    file.open( "file.txt", ios::in );
    if( !file.good() )
    {
        cout << "Nie wczytano pliku!";
    }
    else
    {
        while( getline( file, line ) )
        {

        }
    }

    file.close();
}

void loading_two()
{
    string line;
    char bufor[ 30 ];
    FILE* file = NULL;

    file = fopen( "file.txt", "r" );
    if( file == NULL )
    {
        perror( "" );
    }
    else
    {
        while( !feof( file ) )
        {
            if( fgets( bufor, 30, file ) )
            {
                line = bufor;
            }
        }
    }

    fclose( file );
    file = NULL;
}

int main()
{
    clock_t start, stop;

    start = clock();
    for( int i = 0; i < 100000; i++ )
        loading_one();
    stop = clock();

    cout << "Czas wykonania pierwszego wczytywania: " << static_cast < double > ( stop - start ) / CLOCKS_PER_SEC << endl;

    start = clock();
    for( int i = 0; i < 100000; i++ )
        loading_two();
    stop = clock();

    cout << "Czas wykonania drugiego wczytywania: " << static_cast < double > ( stop - start ) / CLOCKS_PER_SEC << endl;

    return 0;
}
