#include "selectionsort.h"

/* selection sort */
void selectionsort( int* tab, int n )
{
    for( int i = 0; i < n; i++ )
    {
        int mini = i;
        for( int j = i + 1; j < n; j++ )
            if( tab[ j ] < tab[ mini ] )
                mini = j;

        if( mini != i )
        {
			int buf = tab[ i ];
			tab[ i ] = tab[ mini ];
			tab[ mini ] = buf;
        }
    }
}