#include <stdio.h>

int main ()
{
    if( remove( "myfile.txt" ) != 0 )
        perror( "Error deleting file" );
    else
        puts( "File successfully deleted" );

    return 0;
}
