#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

int main ()
{
    FILE * file = NULL;
    long s;
    char * buffer;
    size_t result;

    file = fopen ( "file.txt" , "r" );
    if ( file == NULL )
    {
        perror( "File error" );
    }
    else
    {
        // obtain file size:
        fseek ( file , 0 , SEEK_END );
        s = ftell ( file );
        rewind ( file );

        // allocate memory to contain the whole file:
        buffer = static_cast < char* > ( malloc ( sizeof( char )* s ) );
        if ( buffer == NULL  )
        {
            perror( "Memory error" );
        }
        else
        {
            // copy the file into the buffer:
            result = fread ( buffer, 1, s, file );

            if ( result != static_cast < size_t > ( s ) )
            {
                perror( "Reading error" );
            }

            printf( "%s", buffer );

        }
        cout << endl << sizeof( buffer );
    }

    fclose ( file );
    file = NULL;
    free ( buffer );

    return 0;
}
