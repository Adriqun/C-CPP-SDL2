#include<iostream>
#include <time.h>
#include <cstdlib>
using namespace std;

void merge_helper( int* tab, int s, int mid, int e )
{
    int newtab[ e - s + 1 ];
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
}

void merge( int* tab, int s, int e )
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

int main()
{
    srand( static_cast <int> ( time( NULL ) ) );

    int n;
    int* tab = NULL;

    cin >> n;
    tab = new int [ n ];

    for( int i = 0; i < n; i ++ )
    {
        tab[ i ] = rand() % 100;
    }

    merge( tab, 0, n );


    delete [] tab;

    return 0;
}
