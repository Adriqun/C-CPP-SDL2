/* isgraph example */
#include <stdio.h>
#include <ctype.h>
int main ()
{
  FILE* file = NULL;
  int c;

  file = fopen( "myfile.txt", "r" );

  if( file )
  {
    do {
      c = fgetc ( file );
      if ( isgraph( c ) )
        putchar ( c );

    } while ( c != EOF );

    fclose ( file );
  }
}
