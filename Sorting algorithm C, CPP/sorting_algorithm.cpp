#include "sorting_algorithm.h"
#include <algorithm>
#include <stdio.h>

int sorting::max( int x, int y )
{
    if( x > y ) return x;
    else        return y;
}

/*
void sorting::merge_helper( int* tab, int s, int mid, int e )
{
    int* newtab = new int [ (e - s) + 1 ];
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

    delete [] newtab;
}
*/

void sorting::max_heapify( int* a, int i, int n )
{
    int j, temp;
    temp = a[ i ];
    j = 2 * i;

    while( j <= n )
    {
        if( j < n && a[ j + 1 ] > a[ j ] )
            j = j + 1;

        if( temp > a[ j ] )
            break;

        else if( temp <= a[ j ] )
        {
            a[ j / 2 ] = a[ j ];
            j = 2 * j;
        }
    }

    a[ j / 2 ] = temp;

    return;
}

void sorting::build_maxheap( int* a, int n )
{
    int i;
    for( i = n/2; i >= 1; i-- )
    {
        max_heapify( a, i, n );
    }
}

void sorting::countSort( int* arr, int n, int exp )
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

void sorting::bitonic_helper( int* data, int n, int low, int dir )
{
    if( n > 1 )
    {
        int k = n / 2;
        for( int i = low; i < low + k; i++ )
        {
            if( dir == ( data[ i ] > data[ i+k ] ) )
            {
                std::swap( data[ i ], data[ i+k ] );
            }
        }

        bitonic_helper( data, k, low, dir );
        bitonic_helper( data, k, low+k, dir );
    }
}

/* quick sort */
void sorting::quick(int *tab, int left, int right)
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
            std::swap( tab[ i ], tab[ j ] );
            i++;
            j--;
        }
    }
    while ( i <= j );
    if( j > left )  quick( tab, left, j );
    if( i < right ) quick( tab, i, right );
}

/*
// merge sort
void sorting::merge( int* tab, int s, int e )
{
    int mid;

    if( s != e )
    {
        mid = (s + e) / 2;
        merge( tab, s, mid );
        merge( tab, mid+1, e );
        merge_helper( tab, s, mid, e );
    }
}
*/

/* heap sort */
void sorting::heap( int* a, int n )
{
    build_maxheap( a, n );
    for( int i = n; i >= 2; i-- )
    {
        std::swap( a[ i ], a[ 1 ] );
        max_heapify( a, 1, i - 1 );
    }
}

/* shell sort */
void sorting::shell( int* tab, int n )
{
    for( int gap = n / 2; gap > 0; gap /= 2 )
    {
        for( int i = gap; i < n; i++)
        {
            for( int j = i-gap; j >= 0 && tab[ j ]> tab[ j + gap ]; j -= gap )
            {
                std::swap( tab[ j ], tab[ j + gap ] );
            }
        }
    }
}

/* counting sort */
void sorting::counting( int* tab, int n )
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

/* radix sort */
void sorting::radix( int* arr, int n )
{
    int m = 0;
    for( int i = 0; i < n; i++ )
        if( arr[ i ] > m )
            m = arr[ i ];

    for( int i = 1; m / i > 0; i *= 10 )
        countSort( arr, n, i );
}

/* bitonic sort */
void sorting::bitonic( int* data, int n, int low, int buf )
{
    if( n > 1 )
    {
        bitonic( data, n / 2, low, 1 );
        bitonic( data, n / 2, low + n / 2, 0 );
        bitonic_helper( data, n, low, buf );
    }
}

/* cocktail sort */
void sorting::cocktail( int* arr, int len )
{
    bool notSorted = true;
    while( notSorted )
    {
        notSorted = false;
        for( int a = 0; a < len - 1; a++ )
        {
            if( arr[ a ] > arr[ a + 1 ] )
            {
                std::swap( arr[ a ], arr[ a + 1 ] );
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
                std::swap( arr[ a ], arr[ a - 1 ] );
                notSorted = true;
            }
        }
    }
}

/* bubble sort */
void sorting::bubble( int* tab, int n )
{
    for( int i = 1; i < n; i++ )
    {
        for( int j = n-1 ; j >= 1; j-- )
        {
            if( tab[ j ] < tab[ j - 1 ] )
            {
                std::swap( tab[ j - 1 ], tab[ j ] );
            }
        }
    }
}

/* selection sort */
void sorting::selection( int* tab, int n )
{
    for( int i = 0; i < n; i++ )
    {
        int mini = i;
        for( int j = i + 1; j < n; j++ )
            if( tab[ j ] < tab[ mini ] )
                mini = j;

        if( mini != i )
        {
            std::swap( tab[ i ], tab[ mini ] );
        }
    }
}

/* insertion sort */
void sorting::insertion( int* tab, int n )
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


