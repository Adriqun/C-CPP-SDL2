/* cosh example */
#include <stdio.h>      /* printf */
#include <math.h>       /* cosh, log */

int main ()
{
  double param = log( 2.0 );
  double result;

  result = cosh( param );
  printf( "The hyperbolic cosine of %f is %f.\n", param, result );

  return 0;
}
