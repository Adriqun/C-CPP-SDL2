#include "countingsort.h"

/* counting sort */
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