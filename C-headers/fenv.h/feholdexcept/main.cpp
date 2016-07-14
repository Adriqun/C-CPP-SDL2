/* feholdexcept/feupdateenv example */
#include <stdio.h>      /* printf, puts */
#include <fenv.h>       /* feholdexcept, feclearexcept, fetestexcept, feupdateenv, FE_* */
#include <math.h>       /* log */
#pragma STDC FENV_ACCESS on

double log_zerook (double x)
{
    fenv_t fe;

    feholdexcept( &fe );
    x = log( x );

    feclearexcept( FE_OVERFLOW | FE_DIVBYZERO );
    feupdateenv( &fe );

    return x;
}

int main ()
{
    feclearexcept( FE_ALL_EXCEPT );
    printf( "log(0.0): %f\n", log_zerook( 0.0 ) );

    if( !fetestexcept( FE_ALL_EXCEPT ) )
        puts( "no exceptions raised" );

    return 0;
}
