#include "shellsort.h"

/* shell sort */
void shellsort( int* tab, int n )
{
    for( int gap = n / 2; gap > 0; gap /= 2 )
    {
        for( int i = gap; i < n; i++)
        {
            for( int j = i-gap; j >= 0 && tab[ j ]> tab[ j + gap ]; j -= gap )
            {
				int buf = tab[ j ];
				tab[ j ] = tab[ j + gap ];
				tab[ j + gap ] = buf;
            }
        }
    }
}