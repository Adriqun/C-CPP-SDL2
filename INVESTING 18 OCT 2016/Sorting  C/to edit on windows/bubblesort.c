#include "bubblesort.h"

/* bubble sort */
void bubblesort( int* tab, int n )
{
    for( int i = 1; i < n; i++ )
    {
        for( int j = n-1 ; j >= 1; j-- )
        {
            if( tab[ j ] < tab[ j - 1 ] )
            {
				int buf = tab[ j - 1 ];
				tab[ j - 1 ] = tab[ j ];
				tab[ j ] = buf;
            }
        }
    }
}