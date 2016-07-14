#include <stdio.h>

int main()
{
    FILE* file = NULL;
    char buffer[ 100 ];

    file = fopen( "plik.txt", "r" );

    if( file == NULL )
    {
        // rozni sie tym ze pokaze nam blad, gdybysmy uzyli printf to o niczym nie wiemy
        perror( "Error" );
    }
    else
    {
        // dopoki nie bedzie koniec linii
        while( !feof( file ) )
        {
            if( fgets( buffer, 100, file ) )
                fputs( buffer, stdout );

        }

    }

    fclose( file );
    file = NULL;

    return 0;
}
/*
 INFORMACJE 2016.02.29
Obiekt zawierajacy informacje do sterowania strumieniem.

Typ obiektu kt�ry identyfikuje strumien i zawiera informacje
potrzebne do kontrolowania ich, w tym wska�nik do bufora,
jego wskaznik polozenia i wszystkie jego wskazniki stanu.

Obiekty pliku sa zwykle tworzone przez wywolanie albo fopen
lub tmpfile, kt�re zwracaja wskaznik do jednego z tych obiekt�w.
*/
