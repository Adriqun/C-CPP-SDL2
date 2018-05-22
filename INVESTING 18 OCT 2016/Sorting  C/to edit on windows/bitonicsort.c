#include "bitonicsort.h"

void bitonic_helper( int* data, int n, int low, int dir )
{
    if( n > 1 )
    {
        int k = n / 2;
        for( int i = low; i < low + k; i++ )
        {
            if( dir == ( data[ i ] > data[ i+k ] ) )
            {
				int buf = data[ i ];
				data[ i ] = data[ i+k ];
				data[ i+k ] = buf;
            }
        }

        bitonic_helper( data, k, low, dir );
        bitonic_helper( data, k, low+k, dir );
    }
}

/* bitonic sort */
void bitonicsort( int* data, int n, int low, int buf )
{
    if( n > 1 )
    {
        bitonicsort( data, n / 2, low, 1 );
        bitonicsort( data, n / 2, low + n / 2, 0 );
        bitonic_helper( data, n, low, buf );
    }
}