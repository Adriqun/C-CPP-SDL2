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


int main( int argc, char** argv )
{
    int n = 0;
    int* a = NULL;
    int* b = NULL;
    clock_t start;

    while( true )
    {
        int min = 0;
        int max = 45000000;

        mycout( "| Comparison between sorting algorithms on integers |\n\n", 15 );
        mycout( "Hi! Tell me how many numbers in array you want? " );
        scanf( "%d", &n );

        if( n < min || n > max  )
        {
            mycout( "You need to write n > 0 and n < 4.5 * 10^7 !\n", 12 );
            Sleep( 5000 );
            system( "cls" );
        }
        else
            break;
    }


    /* Creating formula array and test array */
    a = new int [ n ];
    b = new int [ n ];

    /* Seed rand*/
    srand( static_cast <int> ( time( NULL ) ) );


    /* Random numbers in array */
    for( int i = 0; i < n ; i++ )
    {
        a[ i ] = rand() % 100;
    }


////////////////////////////////////////////////////////////////////////////////////////////////////////////


    /* counting_sort */
    for( int i = 0; i < n; i++ )
        b[ i ] = a[ i ];
    start = clock();

    mycout( "\n\n1. counting sort", 10 );
    sorting::counting( b, n );
    printf( "  time %f\n", (float) ( clock() - start ) / CLOCKS_PER_SEC );


////////////////////////////////////////////////////////////////////////////////////////////////////////////


    /* radix sort */
    for( int i = 0; i < n; i++ )
        b[ i ] = a[ i ];
    start = clock();

    mycout( "2. radix sort", 2 );
    sorting::radix( b, n );
    printf( "\t  time %f\n", (float) ( clock() - start ) / CLOCKS_PER_SEC );


////////////////////////////////////////////////////////////////////////////////////////////////////////////


    /* quick_sort */
    for( int i = 0; i < n; i++ )
        b[ i ] = a[ i ];
    start = clock();

    mycout( "3. quick sort", 2 );
    sorting::quick( b, 0, n );
    printf( "\t  time %f\n", (float) ( clock() - start ) / CLOCKS_PER_SEC );


////////////////////////////////////////////////////////////////////////////////////////////////////////////


    /* heap_sort */
    for( int i = 0; i < n; i++ )
        b[ i ] = a[ i ];
    start = clock();

    mycout( "4. heap sort", 11 );
    sorting::heap( b, n );
    printf( "\t  time %f\n", (float) ( clock() - start ) / CLOCKS_PER_SEC );


////////////////////////////////////////////////////////////////////////////////////////////////////////////


    /* shell_sort */
    for( int i = 0; i < n; i++ )
        b[ i ] = a[ i ];
    start = clock();

    mycout( "5. shell sort", 3 );
    sorting::shell( b, n );
    printf( "\t  time %f\n", (float) ( clock() - start ) / CLOCKS_PER_SEC );


////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*

    // merge_sort
    for( int i = 0; i < n; i++ )
        b[ i ] = a[ i ];
    start = clock();

    mycout( "6. merge sort", 3 );
    sorting::merge( b, 0, n );
    printf( "\t  time %f\n", (float) ( clock() - start ) / CLOCKS_PER_SEC );
*/

////////////////////////////////////////////////////////////////////////////////////////////////////////////


    /* bitonic sort */
    for( int i = 0; i < n; i++ )
        b[ i ] = a[ i ];
    start = clock();

    mycout( "6. bitonic sort", 13 );
    sorting::bitonic( b, n, 0, 1 );
    printf( "   time %f\n", (float) ( clock() - start ) / CLOCKS_PER_SEC );


////////////////////////////////////////////////////////////////////////////////////////////////////////////


    /* insertion sort */
    for( int i = 0; i < n; i++ )
        b[ i ] = a[ i ];
    start = clock();

    mycout( "7. insertion sort", 12 );
    sorting::insertion( b, n );
    printf( " time %f\n", (float) ( clock() - start ) / CLOCKS_PER_SEC );


////////////////////////////////////////////////////////////////////////////////////////////////////////////


    /* selection sort */
    for( int i = 0; i < n; i++ )
        b[ i ] = a[ i ];
    start = clock();

    mycout( "8. selection sort", 4 );
    sorting::selection( b, n );
    printf( " time %f\n", (float) ( clock() - start ) / CLOCKS_PER_SEC );


////////////////////////////////////////////////////////////////////////////////////////////////////////////


    /* cocktail sort */
    for( int i = 0; i < n; i++ )
        b[ i ] = a[ i ];
    start = clock();

    mycout( "9. cocktail sort", 4 );
    sorting::cocktail( b, n );
    printf( "  time %f\n", (float) ( clock() - start ) / CLOCKS_PER_SEC );


////////////////////////////////////////////////////////////////////////////////////////////////////////////


    /* bubble sort */
    for( int i = 0; i < n; i++ )
        b[ i ] = a[ i ];
    start = clock();

    mycout( "10.bubble sort", 4 );
    sorting::bubble( b, n );
    printf( "   time %f\n", (float) ( clock() - start ) / CLOCKS_PER_SEC );


////////////////////////////////////////////////////////////////////////////////////////////////////////////


    delete [] a;
    delete [] b;

    system( "PAUSE" );

    return 0;
}
