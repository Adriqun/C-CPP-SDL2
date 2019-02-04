#include <stdio.h>

int main ()
{
    freopen( "myfile.txt","w",stdout );

    printf( "This sentence is redirected to a file." );
    printf( "\nSeriously?" );

    fclose( stdout );

    return 0;
}
