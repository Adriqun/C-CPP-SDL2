#include <stdio.h>      /* printf */
#include <math.h>       /* erf */

// zwiazane z liczbami zespolonymi!

int main ()
{
    double param, result;
    param = 1.0;
    result = erf (param);
    printf ("erf (%f) = %f\n", param, result );
    return 0;
}
