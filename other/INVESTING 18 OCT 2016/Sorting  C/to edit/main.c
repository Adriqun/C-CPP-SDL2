#include "text.h"
#include "console.h"
#include "array.h"


#include "countingsort.h"
#include "radixsort.h"
#include "quicksort.h"
#include "heapsort.h"
#include "shellsort.h"
#include "mergesort.h"
#include "bitonicsort.h"
#include "insertionsort.h"
#include "selectionsort.h"
#include "cocktailsort.h"
#include "bubblesort.h"

int main( int argc, char** argv )
{
	int SCREEN_WIDTH = getWidth();
	int SCREEN_HEIGHT = getHeight();
	
	
	array.n = 0;
	array.a = NULL;
	array.b = NULL;
	
	
	while( true )
	{
		int min = 0;
		int max = 45000000; // 45 milion
		
		printf( "%s", WHITEBOLD );
		centre( SCREEN_WIDTH, "Comparison between sorting algorithms on integers\n\n" );
		clear();
		
		printf( "How many numbers: " );
		scanf( "%d", &array.n );
		
		if( array.n < min || array.n > max  )
        {
            printf( "%sYou need to write 0 < n < 4.5 * 10^7 !\n", LREDBOLD );
            usleep( 5000000 ); // Takes microsecons!
			system( "tput reset" );	// "reset" is too slowly
        }
        else
		{
			break;
		}
	}
	
	
	// Creating formula array and test array 
    array.a = malloc( array.n * sizeof( int ) );
    array.b = malloc( array.n * sizeof( int ) );
	
	// Seed rand
    srand( ( int ) ( time( NULL ) ) );
	
	// Our time
	clock_t start;
	
	// Random numbers in array
    for( int i = 0; i < array.n ; i++ )
    {
        array.a[ i ] = rand() % 100;
    }
	
	
	// counting_sort
    for( int i = 0; i < array.n; i++ )	array.b[ i ] = array.a[ i ]; 	// copy
    start = clock();													// set clock
	printf( "%s\n1. counting sort", LBLUE );	clear();				// cout and clear
    countingsort( array.b, array.n );
    printf( "  time %f\n", (float) ( clock() - start ) / CLOCKS_PER_SEC );
	
	
	// radix sort
    for( int i = 0; i < array.n; i++ )	array.b[ i ] = array.a[ i ]; 	// copy
    start = clock();													// set clock
	printf( "%s2. radix sort", BLUE );	clear();
    radixsort( array.b, array.n );
    printf( "\t  time %f\n", (float) ( clock() - start ) / CLOCKS_PER_SEC );
	
	
	// quicksort
	for( int i = 0; i < array.n; i++ )	array.b[ i ] = array.a[ i ]; 	// copy
    start = clock();													// set clock
	printf( "%s3. quick sort", BLUE );	clear();
    quicksort( array.b, 0, array.n );
    printf( "\t  time %f\n", (float) ( clock() - start ) / CLOCKS_PER_SEC );
	
	
	/* heapsort */
    for( int i = 0; i < array.n; i++ )	array.b[ i ] = array.a[ i ]; 	// copy
    start = clock();													// set clock
	printf( "%s4. heap sort", LCYAN );	clear();
    heapsort( array.b, array.n );
    printf( "\t  time %f\n", (float) ( clock() - start ) / CLOCKS_PER_SEC );
	
	
	/* shellsort */
    for( int i = 0; i < array.n; i++ )	array.b[ i ] = array.a[ i ]; 	// copy
    start = clock();													// set clock
	printf( "%s5. shell sort", CYAN );	clear();
    shellsort( array.b, array.n );
    printf( "\t  time %f\n", (float) ( clock() - start ) / CLOCKS_PER_SEC );
	
	
	// merge sort
    for( int i = 0; i < array.n; i++ )	array.b[ i ] = array.a[ i ]; 	// copy
    start = clock();													// set clock
	printf( "%s6. merge sort", CYAN );	clear();
    mergesort( array.b, 0, array.n );
    printf( "\t  time %f\n", (float) ( clock() - start ) / CLOCKS_PER_SEC );
	
	
	/* bitonic sort */
    for( int i = 0; i < array.n; i++ )	array.b[ i ] = array.a[ i ]; 	// copy
    start = clock();													// set clock
	printf( "%s7. bitonic sort", LGREEN );	clear();
    bitonicsort( array.b, array.n, 0, 1 );
    printf( "   time %f\n", (float) ( clock() - start ) / CLOCKS_PER_SEC );
	
	
	/* insertion sort */
    for( int i = 0; i < array.n; i++ )	array.b[ i ] = array.a[ i ]; 	// copy
    start = clock();													// set clock
	printf( "%s8. insertion sort", GREEN );	clear();
    insertionsort( array.b, array.n );
    printf( " time %f\n", (float) ( clock() - start ) / CLOCKS_PER_SEC );
	
	
	/* selection sort */
    for( int i = 0; i < array.n; i++ )	array.b[ i ] = array.a[ i ]; 	// copy
    start = clock();													// set clock
	printf( "%s9. selection sort", GREEN );	clear();
    selectionsort( array.b, array.n );
    printf( " time %f\n", (float) ( clock() - start ) / CLOCKS_PER_SEC );
	
	
	/* cocktail sort */
    for( int i = 0; i < array.n; i++ )	array.b[ i ] = array.a[ i ]; 	// copy
    start = clock();													// set clock
	printf( "%s10. cocktail sort", LMAGENTA );	clear();
    cocktailsort( array.b, array.n );
    printf( " time %f\n", (float) ( clock() - start ) / CLOCKS_PER_SEC );
	
	
	/* bubble sort */
    for( int i = 0; i < array.n; i++ )	array.b[ i ] = array.a[ i ]; 	// copy
    start = clock();													// set clock
	printf( "%s11. bubble sort", MAGENTA );	clear();
    bubblesort( array.b, array.n );
    printf( "   time %f\n\n", (float) ( clock() - start ) / CLOCKS_PER_SEC );
	
	free( array.a );
	free( array.b );
	
	getchar();
	
	return 0;
}