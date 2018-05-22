#include <iostream>
#include <stdlib.h>

using namespace std;

/*
// malejaco
int compare( const void* a, const void* b )
{
    int* arg1 = (int*) a;
    int* arg2 = (int*) b;

    if( *arg1 > *arg2 )         return -1;
    else if( *arg1 == *arg2 )   return 0;
    else                        return 1;
}
*/
// malejaco
int compare( const void * a, const void * b )
{
    return ( *(int*)b - *(int*)a );
}

int main()
{
    int t;
    cin >> t;
    while( t-- )
    {
        int number;
        int max_weight;
        cin >> number >> max_weight;

        int* tab = new int [ number ];
        for( int i = 0; i < number; i++ )
            cin >> tab[ i ];

        qsort( tab, number, sizeof( int ), compare );

        int counter = 0;
        int minimum = number/2 + number%2;

        int j = 1;
        for( int i = 0; i < number; i++ )
        {
            if( i > number - j )
                break;

            if( tab[ i ] + tab[ number - j ] <= max_weight )    j++;

            counter++;
        }

        cout << ( (counter > minimum) ? counter : minimum ) << endl;
    }

    return 0;
}
