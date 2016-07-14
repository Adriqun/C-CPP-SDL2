#include <iostream>
#include <stdio.h>

using namespace std;

int main()
{
    int tablica[ 256 ];
    for( int i = 0; i < 256; i++ )
        tablica[ i ] = 0;

    unsigned char znak;
    while( scanf( "%c", &znak ) != EOF )
        tablica[ static_cast <int> (znak) ] ++;

    for( int i = 0; i < 256; i ++ )
        if( tablica[ i ] > 0 ) cout << i << " " << tablica[ i ] << endl;


    return 0;
}
