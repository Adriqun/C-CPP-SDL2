#include <stdio.h>
#include <ctype.h>

// sprawdza czy znak jest wielka litera, mala litera albo cyfra

int main ()
{
  int i;
  char str[] = "c3po...";

  i = 0;
  while( isalnum( str[ i ] ) )
        i++;

  printf ( "The first %d characters are alphanumeric.\n", i );

  return 0;
}
