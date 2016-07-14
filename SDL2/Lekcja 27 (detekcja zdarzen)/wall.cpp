#include "wall.h"

Wall::Wall()
{
    WIDTH = 128;
    HEIGHT = 128;
    VEL = 5;

    number = 0;
}

int Wall::fast_atoi( std::string path )
{
    int num = 0, buf;
    for( uint8_t i = 0; i < path.length(); i++ )
    {
        buf = ( int ) path[ i ] - 48;
        for( uint8_t j = 1; j < path.length() - i; j++ )    buf *= 10;
        num += buf;
    }
    return num;
}

void Wall::loadFile( std::string path )
{
    std::string line;

    // otwieranie pliku i liczenie pozycji
    file.open( path.c_str(), std::ios::in );

    if( file.good() )
    {
        while( getline( file, line ) )
        {
            number ++;
        }
    }

    file.close();

    // tworzenie miejsca w pamieci na dane
    rect = new SDL_Rect [ number ];
    number = 0;

    // otwieranie pliku i zapis danych
    file.open( path.c_str(), std::ios::in );

    if( file.good() )
    {
        std::string bufor;

        while( getline( file, line ) )
        {
            for( uint8_t i = 0; i < line.length(); i++ )
            {
                if( line[ i ] == '.' )
                {
                    rect[ number ].x = fast_atoi( bufor );
                    bufor.clear();

                    for( uint8_t j = i + 1; j < line.length(); j++ )
                    {
                        if( line[ j ] == '.' )
                        {
                            rect[ number ].y = fast_atoi( bufor );
                            bufor.clear();

                            break;
                        }

                        bufor += line[ j ];
                    }

                    break;
                }

                bufor += line[ i ];
            }

            number ++;
        }
    }

    file.close();
}

void Wall::move()
{
    for( uint16_t i = 0; i < number; i++ )
        rect[ i ].x --;
}

SDL_Rect Wall::getRect()
{
    static int counter;

    counter ++;

    if( counter == number )
        counter = 0;

    return rect[ counter ];
}

void Wall::render( SDL_Renderer* &renderer )
{
    for( uint16_t i = 0; i < number; i++ )
        texture.render( renderer, rect[ i ].x, rect[ i ].y );
}
