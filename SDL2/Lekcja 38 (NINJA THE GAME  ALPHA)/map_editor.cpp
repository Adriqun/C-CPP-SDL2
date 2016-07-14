#include "map_editor.h"
#include <stdio.h>

Chart::Chart()
{
    how_many = 14;

    counter = new uint16_t [ how_many ];
    texture = new SDL_Texture* [ how_many ];
    arect = new SDL_Rect* [ how_many ];
    brect = new SDL_Rect* [ how_many ];

    for( uint8_t i = 0; i < how_many; i++ )
    {
        texture[ i ] = NULL;
        arect[ i ] = NULL;
        brect[ i ] =  NULL;
        counter[ i ] = 0;
    }
}

Chart::~Chart()
{
    counter = NULL;

    for( uint8_t i = 0; i < how_many; i++ )
    {
        texture[ i ] = NULL;
        arect[ i ] = NULL;
        brect[ i ] = NULL;
    }
}

void Chart::close()
{
    for( uint8_t i = 0; i < how_many; i++ )
    {
        for( uint8_t j = 0; j < counter[ i ]; j++ )
        {
            delete [] arect[ j ];
            delete [] brect[ j ];
        }
    }

    delete [] arect;
    delete [] brect;
    delete [] counter;
    delete [] texture;
}

void Chart::load_texture( SDL_Texture* _texture )
{
    static uint8_t i;

    texture[ i ] = _texture;

    if( i == 13 )
        delete &i;
    else
        i++;
}

int Chart::string_to_int( std::string path )
{
    int num = 0, buf;

    for( uint8_t i = 0; i < path.length(); i++ )
    {
        buf = ( int ) path[ i ] - 48;
        for( uint8_t j = 1; j < path.length() - i; j++ )
            buf *= 10;
        num += buf;
    }

    return num;
}

void Chart::set_rect( SDL_Rect &rect, std::string &draft )
{
    std::string bufor;

    for( uint8_t i = 0; i < draft.length(); i++ )
    {
        if( draft[ i ] == '.' )
        {
            for( uint8_t j = i + 1; i < draft.length(); j++ )
            {
                if( draft[ j ] == '.' )
                {
                    rect.x = string_to_int( bufor );
                    bufor.clear();

                    for( uint8_t k = j + 1; k < draft.length(); k++ )
                    {
                        if( draft[ k ] == '.' )
                        {
                            rect.y = string_to_int( bufor );
                            rect.w = 128;
                            rect.h = 128;

                            break;
                        }
                        else
                            bufor += draft[ k ];
                    }

                    break;
                }
                else
                    bufor += draft[ j ];
            }

            break;
        }
    }
}

void Chart::load_file()
{
    // faza I, wczytanie i zrobienie miejsca w pamieci

    for( uint8_t i = 0; i < how_many; i++ )
        counter[ i ] = 0;

    file.open( "files/map.txt", std::ios::in );

    if( !file.good() )
    {
        printf( "Nie wczytano pliku map.txt!\n" );
    }
    else
    {
        std::string line;
        std::string buf;
        uint8_t nr;

        while( getline( file, line ) )
        {
            for( uint8_t i = 0; i < line.length(); i++ )
            {
                if( line[ i ] == '.' )
                {
                    nr = string_to_int( buf );
                    buf.clear();
                    break;
                }

                buf += line[ i ];
            }

            counter[ nr ]++;
        }

        for( uint8_t i = 0; i < how_many; i++ )
        {
            arect[ i ] = new SDL_Rect [ counter[ i ] ];
            brect[ i ] = new SDL_Rect [ counter[ i ] ];
        }

    }

    file.close();



    // faza II, wczytanie do zrobionych wczesniej miejsc w pamieci i ustawienie licznikow
    file.open( "files/map.txt", std::ios::in );

    if( !file.good() )
    {
        printf( "Nie wczytano pliku map.txt!\n" );
    }
    else
    {
        for( uint8_t i = 0; i < how_many; i++ )
            counter[ i ] = 0;

        std::string line;
        std::string buf;
        uint8_t nr;

        while( getline( file, line ) )
        {

            for( uint8_t i = 0; i < line.length(); i++ )
            {
                if( line[ i ] == '.' )
                {
                    nr = string_to_int( buf );
                    buf.clear();
                    break;
                }

                buf += line[ i ];
            }

            set_rect( arect[ nr ][ counter[ nr ] ], line );
            counter[ nr ]++;
        }

        for( uint8_t i = 0; i < how_many; i++ )
        {
            for( uint16_t j = 0; j < counter[ i ]; j++ )
            {
                brect[ i ][ j ] = arect[ i ][ j ];
            }
        }
    }

    file.close();
}

void Chart::add_to_file( std::string data )
{
    if( data != "F" )
    {
        file.open( "files/map.txt", std::ios::out | std::ios::app );

        if( !file.good() )
            printf( "Nie wczytano pliku map.txt!\n" );
        else
            file << data << "\n";

        file.close();

        load_file();
    }
}

void Chart::draw_block( SDL_Renderer* &renderer, SDL_Point point, uint8_t type )
{
    SDL_Rect rect;
    rect.w = 128;
    rect.h = 128;
    rect.x = point.x;
    rect.y = point.y;

    SDL_RenderCopy( renderer, texture[ type ], NULL, &rect );
}

void Chart::draw( SDL_Renderer* &renderer, SDL_Rect _rect )
{
    for( uint8_t i = 0; i < how_many; i++ )
    {
        for( uint16_t j = 0; j < counter[ i ]; j++ )
        {
            arect[ i ][ j ].x = brect[ i ][ j ].x - _rect.x;

            SDL_RenderCopy( renderer, texture[ i ], NULL, &arect[ i ][ j ] );
        }
    }
}

SDL_Rect Chart::get_rect( uint16_t i, uint16_t j )
{
    return arect[ i ][ j ];
}
