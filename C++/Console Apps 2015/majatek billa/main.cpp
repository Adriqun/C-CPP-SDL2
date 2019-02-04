#include <stdio.h>
#include <cstdlib>

int power_modulo_fast( int* a, int* b, int* m )
{
    int result = 1;
    long int x = *a % *m;

    for ( int i = 1; i <= *b; i <<=1 )
    {
        x %= *m;
        if ( ( *b&i ) != 0 )
        {
            result *= x;
            result %= *m;
        }
        x *= x;
    }

    return result;
}

int main()
{
    int *a = new int, *b = new int, *c = new int;

    while( scanf( "%d %d %d", a, b, c ) )
    {
        if( *a == 0 && *b == 0 && *c == 0 ) break;
        printf( "%d\n", power_modulo_fast( a, b, c ) );
    }

    return 0;
}
