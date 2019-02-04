#include <iostream>
#include <stdio.h>

using namespace std;

int main()
{
    int t, n;
    int two, three, five, seven;

    cin >> t;

    while( t-- )
    {
        cin >> n;

        if( n < 10 )
        {
            printf( "%d\n", n ?: 10 );
            continue;
        }

        two = three = five = seven = 0;

        while( n%2 == 0 ) ++two,      n >>= 1;
        while( n%3 == 0 ) ++three,    n /= 3;
        while( n%5 == 0 ) ++five,     n /= 5;
        while( n%7 == 0 ) ++seven,    n /= 7;

        if( n > 1 )
        {
            printf( "NIE\n" );
            continue;
        }

        if( two%3 == 1 && three%2 == 0 || two%3 == 2 && three%2 )   printf( "2" ),  --two;
        if( three%2 && two%3 == 0 )                                 printf( "3" ),  --three;
        if( two%3 == 2 && three%2 == 0 )                            printf( "4" ),  two -= 2;

        for( int i = 0; i < five; ++i )                             printf( "5" );

        if( two%3 == 1 && three%2 )                                 printf("6"),    --two,  --three;

        for( int i = 0; i < seven; ++i )                            printf("7");
        for( int i = 0; i < two/3; ++i )                            printf("8");
        for( int i = 0; i < three>>1; ++i )                         printf("9");

        printf( "\n" );
    }

    return 0;
}
