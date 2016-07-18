#include <stdio.h>      /* printf */
#include <stdarg.h>     /* va_list, va_start, va_arg, va_end */

void PrintFloats( int n, ... )
{
    double val;
    va_list vl;

    va_start( vl, n );

    for( int i = 0; i < n; i ++ )
    {
        val = va_arg( vl, double );
        printf (" [%.2f]", val );
    }

    va_end( vl );
}

int main ()
{

    printf ("Printing floats:");
    PrintFloats( 3, 3.14159, 2.71828, 1.41421 );
    printf ( "\n" );

    return 0;
}
