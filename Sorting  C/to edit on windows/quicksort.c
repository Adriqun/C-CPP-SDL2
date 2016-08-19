#include "quicksort.h"

/* quicksort */
void quicksort(int *tab, int left, int right)
{
    int v = tab[ ( left + right ) / 2 ];
    int i = left;
    int j = right;

    do
    {
        while ( tab[ i ] < v ) i++;
        while ( tab[ j ] > v ) j--;
        if( i <= j)
        {
			int buf = tab[ i ];
			tab[ i ] = tab[ j ];
			tab[ j ] = buf;
			
            i++;
            j--;
        }
    }
    while ( i <= j );
    if( j > left )  quicksort( tab, left, j );
    if( i < right ) quicksort( tab, i, right );
}