/* atanh example */
#include <stdio.h>      /* printf */
#include <math.h>       /* tanh, atanh */

int main ()
{
  double param= tanh( 1 );
  double result;

  result = atanh(param) ;
  printf ( "The arc hyperbolic tangent of %f is %f radians.\n", param, result );

  return 0;
}
