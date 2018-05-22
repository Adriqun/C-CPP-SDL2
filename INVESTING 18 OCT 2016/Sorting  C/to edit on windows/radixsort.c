#include "radixsort.h"
#include <stdlib.h>

void countSort( int* arr, int n, int exp )
{
    int* output = (int*) (malloc( n * sizeof( int ) ) );
    int count[ 10 ] = { 0 };

    for( int i = 0; i < n; i++ )
        count[ ( arr[ i ] / exp ) % 10 ]++;

    for( int i = 1; i < 10; i++ )
        count[ i ] += count[ i - 1 ];

    for( int i = n - 1; i >= 0; i-- )
    {
        output[ count[ ( arr[ i ] / exp ) % 10 ] - 1 ] = arr[ i ];
        count[ ( arr[ i ] / exp ) % 10 ]--;
    }

    for( int i = 0; i < n; i++ )
        arr[ i ] = output[ i ];

    free( output );
}

/* radix sort */
void radixsort( int* arr, int n )
{
    int m = 0;
    for( int i = 0; i < n; i++ )
        if( arr[ i ] > m )
            m = arr[ i ];

    for( int i = 1; m / i > 0; i *= 10 )
        countSort( arr, n, i );
}