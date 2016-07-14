/* sinh example */
#include <stdio.h>      /* printf */
#include <math.h>       /* sinh, log */

int main ()
{
  double param= log( 2.0 );
  double result;

  result = sinh( param );
  printf ( "The hyperbolic sine of %f is %f.\n", param, result );

  return 0;
}
