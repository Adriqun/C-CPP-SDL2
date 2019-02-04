#include <stdio.h>      /* printf */
#include <math.h>       /* exp */

// wykladniczy

int main ()
{
    double param, result;
    param = 5.0;
    result = exp( param );
    printf( "The exponential value of %f is %f.\n", param, result );

    return 0;
}
