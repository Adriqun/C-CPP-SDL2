#include "insertionsort.h"

/* insertion sort */
void insertionsort( int* tab, int n )
{
    for( int j = 1 ; j < n; j++)
    {
        int k = tab[j];
        int i = j-1;

        while(i >= 0 && tab[ i ] > k )
        {
            tab[i + 1] = tab[i];
            i = i - 1;
        }

        tab[ i + 1 ] = k;
    }
}