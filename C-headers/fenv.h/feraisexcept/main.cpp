/* feraiseexcept example */
#include <stdio.h>      /* printf */
#include <fenv.h>       /* feraiseexcept, fetestexcept, FE_ALL_EXCEPT, FE_INVALID */
#pragma STDC FENV_ACCESS on

double fn( double x )    /* some function for which zero is a domain error */
{
    if( x == 0.0 )
        feraiseexcept( FE_INVALID );

    return x;
}

int main ()
{
    feclearexcept( FE_ALL_EXCEPT );
    fn ( 0.0 );

    if ( fetestexcept( FE_INVALID ) )
        printf ( "FE_INVALID raised\n" );

    return 0;
}
