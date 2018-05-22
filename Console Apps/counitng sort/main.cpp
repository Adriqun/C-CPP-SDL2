#include <cstdlib>
#include <stdio.h>
#include <time.h>

void countingsort( int* tab, int n )
{
    int min = 0;
    int max = 0;

    for( int i = 0; i < n; i++ )
    {
        if( tab[ i ] < min ) min = tab[ i ];
        if( tab[ i ] > max ) max = tab[ i ];
    }

    int nr = max - min + 1;
    int bucket[ nr ];

    for( int i = 0; i < nr; i++ )
        bucket[ i ] = 0;

    for( int i = 0; i < n; i++)
        bucket[ tab[ i ] - min ]++;

    int index = 0;
    for( int i = min; i <= max; i++ )
    {
        for( int j = 0; j < bucket[ i - min ]; j++ )
        {
            tab[ index ] = i;
            index++;
        }
    }
}

int main()
{
    /*
        dla 1000000 liczb - success
        dla 1000    liczb - error
    */

    // printf( "Wpisz ile liczb w tablicy: " );

    int n = 100;
    // scanf( "%d", &n );

    int* tab = new int [ n ];

    srand( static_cast <int> ( time( NULL ) ) );

    printf( "\n" );

    for( unsigned i = 0; i < static_cast <unsigned> (n); i++ )
    {
        tab[ i ] = rand() % 100;
        printf( "%d ", tab[ i ] );
    }

    printf( "\n\n" );

    countingsort( tab, n );

    for( unsigned i = 0; i < static_cast <unsigned> (n); i++ )
    {
        printf( "%d ", tab[ i ] );
    }

    printf( "\n" );

    return 0;
}
