#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <cstdlib>
#include "sorting_algorithm.h"

void mycout( const char* text, unsigned color = 7 )
{
    SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ),  color );
    printf( "%s", text );
    SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ),  7 );
}

void ascrib( int* a, int* b, int &n, clock_t &s )
{
    for( int i = 0; i < n; i++ )
    {
        b[ i ] = a[ i ];
    }

    s = clock();
}

int main( int argc, char** argv )
{
    int n = 0;
    while( true )
    {
        mycout( "| Comparison between sorting algorithms with decimal numbers |\n\n", 15 );
        mycout( "Hi! Tell me how many numbers in array you want? " );
        scanf( "%d", &n );

        if( n < 1 || n > 45000000  )
        {
            mycout( "You need to write n > 0 and n < 4.5 * 10^7 !\n", 12 );
            Sleep( 5000 );
            system( "cls" );
        }
        else
            break;
    }



    /* Creating formula array and test array */
    int* a = new int [ n ];
    int* b = new int [ n ];

    /* Seed rand*/
    srand( (int) ( time( NULL ) ) );


    /* Random numbers in array */
    for( int i = 0; i < n ; i++ )
    {
        a[ i ] = rand() % 100;
    }

    clock_t start;

    /* counting_sort */
    ascrib( a, b, n, start );
    mycout( "\n\n1. counting sort", 10 );
    sorting::counting( b, n );
    printf( "  time %f\n", (float) ( clock() - start ) / CLOCKS_PER_SEC );


    /* radix sort */
    ascrib( a, b, n, start );
    mycout( "2. radix sort", 2 );
    sorting::radix( b, n );
    printf( "\t  time %f\n", (float) ( clock() - start ) / CLOCKS_PER_SEC );


    /* quick_sort */
    ascrib( a, b, n, start );
    mycout( "3. quick sort", 2 );
    sorting::quick( b, 0, n );
    printf( "\t  time %f\n", (float) ( clock() - start ) / CLOCKS_PER_SEC );


    /* heap_sort */
    ascrib( a, b, n, start );
    mycout( "4. heap sort", 11 );
    sorting::heap( b, n );
    printf( "\t  time %f\n", (float) ( clock() - start ) / CLOCKS_PER_SEC );


    /* shell_sort */
    ascrib( a, b, n, start );
    mycout( "5. shell sort", 3 );
    sorting::shell( b, n );
    printf( "\t  time %f\n", (float) ( clock() - start ) / CLOCKS_PER_SEC );


    /* merge_sort */
    ascrib( a, b, n, start );
    mycout( "6. merge sort", 3 );
    sorting::merge( b, n );
    printf( "\t  time %f\n", (float) ( clock() - start ) / CLOCKS_PER_SEC );


    /* bitonic sort */
    ascrib( a, b, n, start );
    mycout( "7. bitonic sort", 13 );
    sorting::bitonic( b, n, 0, 1 );
    printf( "   time %f\n", (float) ( clock() - start ) / CLOCKS_PER_SEC );


    /* insertion sort */
    ascrib( a, b, n, start );
    mycout( "8. insertion sort", 12 );
    sorting::insertion( b, n );
    printf( " time %f\n", (float) ( clock() - start ) / CLOCKS_PER_SEC );


    /* selection sort */
    ascrib( a, b, n, start );
    mycout( "9. selection sort", 4 );
    sorting::selection( b, n );
    printf( " time %f\n", (float) ( clock() - start ) / CLOCKS_PER_SEC );


    /* cocktail sort */
    ascrib( a, b, n, start );
    mycout( "10. cocktail sort", 4 );
    sorting::cocktail( b, n );
    printf( " time %f\n", (float) ( clock() - start ) / CLOCKS_PER_SEC );


    /* bubble sort */
    ascrib( a, b, n, start );
    mycout( "11. bubble sort", 4 );
    sorting::bubble( b, n );
    printf( "   time %f\n", (float) ( clock() - start ) / CLOCKS_PER_SEC );


    delete [] a;
    delete [] b;

    system( "PAUSE" );

    return 0;
}
