/* asinh example */
#include <stdio.h>      /* printf */
#include <math.h>       /* asinh, exp, cosh */

int main ()
{
    double param, result;
    param = exp( 2 ) - cosh( 2 );

    result = asinh( param ) ;
    printf ( "The arc hyperbolic sine of %f is %f radians.\n", param, result );

    return 0;
}
