#include <iostream>
#include <cstring>
#include <SDL.h>

using namespace std;

int stringToInt( char* path )
{
    int num = 0, buf;

    for( uint8_t i = 0; i < strlen( path ); i++ )
    {
        buf = static_cast < int > ( path[ i ] ) - 48;
        for( uint8_t j = 1; j < strlen( path ) - i; j++ )
            buf *= 10;
        num += buf;
    }

    return num;
}

void setRect( SDL_Rect &rect, char* path )
{
    char* bufor;

    for( uint8_t i = 2; i < strlen( path ); i++ )
    {
        if( path[ i ] == '.' )
        {
            rect.x = stringToInt( bufor );
            cout << bufor;
            delete [] bufor;

            for( uint8_t j = i + 1; i < strlen( path ); j++ )
            {
                if( path[ j ] == '.' )
                {
                    rect.y = stringToInt( bufor );
                    rect.w = 128;
                    rect.h = 128;

                    break;
                }
                strncat( bufor, &path[ j ], 1 );
            }
            break;
        }
        strncat( bufor, &path[ i ], 1 );
    }
}

int main( int argc, char** argv )
{
    char* cos = "1.50.88.";
    string cos2 = "1.50.88.";
    cout << sizeof (cos) <<endl;

    SDL_Rect rect;
    char b[ 100 ] = "1.50.88.";

    setRect( rect, b );

    cout << rect.x << " " << rect.y << " " << rect.w << " " << rect.h << "\n";

    return 0;
}
