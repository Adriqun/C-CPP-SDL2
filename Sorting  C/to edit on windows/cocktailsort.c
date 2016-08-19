#include "cocktailsort.h"
#include <stdbool.h>

/* cocktail sort */
void cocktailsort( int* arr, int len )
{
    bool notSorted = true;
    while( notSorted )
    {
        notSorted = false;
        for( int a = 0; a < len - 1; a++ )
        {
            if( arr[ a ] > arr[ a + 1 ] )
            {
				int buf = arr[ a ];
				arr[ a ] = arr[ a + 1 ];
				arr[ a + 1 ] = buf;

                notSorted = true;
            }
        }

        if( !notSorted )
            break;

        notSorted = false;

        for( int a = len - 1; a > 0; a-- )
        {
            if( arr[ a - 1 ] > arr[ a ] )
            {
				int buf = arr[ a ];
				arr[ a ] = arr[ a - 1 ];
				arr[ a - 1 ] = buf;

                notSorted = true;
            }
        }
    }
}