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

void setColor( int i )
{
    SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), i );
}

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

		setColor( 15 );
		centre( SCREEN_WIDTH, "Comparison between sorting algorithms on integers\n\n" );
        setColor( 7 );
		printf( "How many numbers: " );
		scanf( "%d", &array.n );

		if( array.n < min || array.n > max  )
        {
            setColor( 12 );
            printf( "You need to write 0 < n < 4.5 * 10^7 !\n" );
            Sleep( 5000 ); // Takes microsecons!
			system( "cls" );	// "reset" is too slowly
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
    setColor( 9 );
	printf( "\n1. counting sort" );
    countingsort( array.b, array.n );
    printf( "  time %f\n", (float) ( clock() - start ) / CLOCKS_PER_SEC );


	// radix sort
    for( int i = 0; i < array.n; i++ )	array.b[ i ] = array.a[ i ]; 	// copy
    start = clock();													// set clock
    setColor( 1 );
	printf( "2. radix sort" );
    radixsort( array.b, array.n );
    printf( "\t  time %f\n", (float) ( clock() - start ) / CLOCKS_PER_SEC );


	// quicksort
	for( int i = 0; i < array.n; i++ )	array.b[ i ] = array.a[ i ]; 	// copy
    start = clock();													// set clock
    setColor( 1 );
	printf( "3. quick sort" );
    quicksort( array.b, 0, array.n );
    printf( "\t  time %f\n", (float) ( clock() - start ) / CLOCKS_PER_SEC );


	/* heapsort */
    for( int i = 0; i < array.n; i++ )	array.b[ i ] = array.a[ i ]; 	// copy
    start = clock();													// set clock
    setColor( 11 );
	printf( "4. heap sort" );
    heapsort( array.b, array.n );
    printf( "\t  time %f\n", (float) ( clock() - start ) / CLOCKS_PER_SEC );


	/* shellsort */
    for( int i = 0; i < array.n; i++ )	array.b[ i ] = array.a[ i ]; 	// copy
    start = clock();													// set clock
    setColor( 3 );
	printf( "5. shell sort" );
    shellsort( array.b, array.n );
    printf( "\t  time %f\n", (float) ( clock() - start ) / CLOCKS_PER_SEC );


	// merge sort
    for( int i = 0; i < array.n; i++ )	array.b[ i ] = array.a[ i ]; 	// copy
    start = clock();													// set clock
    setColor( 3 );
	printf( "6. merge sort" );
    mergesort( array.b, 0, array.n );
    printf( "\t  time %f\n", (float) ( clock() - start ) / CLOCKS_PER_SEC );


	/* bitonic sort */
    for( int i = 0; i < array.n; i++ )	array.b[ i ] = array.a[ i ]; 	// copy
    start = clock();													// set clock
    setColor( 10 );
	printf( "7. bitonic sort" );
    bitonicsort( array.b, array.n, 0, 1 );
    printf( "   time %f\n", (float) ( clock() - start ) / CLOCKS_PER_SEC );


	/* insertion sort */
    for( int i = 0; i < array.n; i++ )	array.b[ i ] = array.a[ i ]; 	// copy
    start = clock();													// set clock
    setColor( 2 );
	printf( "8. insertion sort" );
    insertionsort( array.b, array.n );
    printf( " time %f\n", (float) ( clock() - start ) / CLOCKS_PER_SEC );


	/* selection sort */
    for( int i = 0; i < array.n; i++ )	array.b[ i ] = array.a[ i ]; 	// copy
    start = clock();													// set clock
    setColor( 2 );
	printf( "9. selection sort" );
    selectionsort( array.b, array.n );
    printf( " time %f\n", (float) ( clock() - start ) / CLOCKS_PER_SEC );


	/* cocktail sort */
    for( int i = 0; i < array.n; i++ )	array.b[ i ] = array.a[ i ]; 	// copy
    start = clock();													// set clock
    setColor( 13 );
	printf( "10. cocktail sort" );
    cocktailsort( array.b, array.n );
    printf( " time %f\n", (float) ( clock() - start ) / CLOCKS_PER_SEC );


	/* bubble sort */
    for( int i = 0; i < array.n; i++ )	array.b[ i ] = array.a[ i ]; 	// copy
    start = clock();													// set clock
    setColor( 5 );
	printf( "11. bubble sort" );
    bubblesort( array.b, array.n );
    printf( "   time %f\n\n", (float) ( clock() - start ) / CLOCKS_PER_SEC );
    setColor( 7 );
	free( array.a );
	free( array.b );

	system("pause");

	return 0;
}
