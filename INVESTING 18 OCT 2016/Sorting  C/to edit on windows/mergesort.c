#include "mergesort.h"
#include <stdlib.h>

void merge_helper( int* tab, int s, int mid, int e )
{
    int* newtab = malloc( ((e - s) + 1) *sizeof( int ) );
    int i = s;
    int j = mid + 1;
    int k = 0;

    while( i <= mid && j <= e )
    {
        if( tab[ j ] < tab[ i ] )
        {
            newtab[ k ] = tab[ j ];
            j++;
        }
        else
        {
            newtab[ k ] = tab[ i ];
            i++;
        }
        k++;
    }

    if( i <= mid )
    {
        while( i <= mid )
        {
            newtab[ k ] = tab[ i ];
            i++;
            k++;
        }
    }
    else
    {
        while( j <= e )
        {
            newtab[ k ] = tab[ j ];
            j++;
            k++;
        }
    }

    for( i = 0; i <= e-s; i ++ )
    {
        tab[ s + i ] = newtab[ i ];
    }

    free( newtab );
}


void mergesort( int* tab, int s, int e )
{
    int mid;

    if( s != e )
    {
        mid = (s + e) / 2;
        mergesort( tab, s, mid );
        mergesort( tab, mid+1, e );
        merge_helper( tab, s, mid, e );
    }
}