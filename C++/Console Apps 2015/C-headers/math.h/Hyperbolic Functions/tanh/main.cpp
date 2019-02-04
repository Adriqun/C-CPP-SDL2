/* tanh example */
#include <stdio.h>      /* printf */
#include <math.h>       /* tanh, log */

int main ()
{
    double param = log(2.0);
    double result;

    result = tanh( param );
    printf ( "The hyperbolic tangent of %f is %f.\n", param, result );

    return 0;
}
