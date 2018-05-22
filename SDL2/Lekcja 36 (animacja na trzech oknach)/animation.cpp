#include "animation.h"

An::An()
{
    how_many = 26;
    off_set = 0;

    texture = new SDL_Texture* [ how_many ];

    for( Uint8 y = 0; y < how_many; y ++ )
        texture[ y ] = NULL;
}

An::~An()
{
    delete [] texture;
}

std::string An::int_to_string( int n )
{
    std::string tmp;
    if( n < 0 )
    {
        tmp = "-";
        n = -n;
    }
    if( n > 9 )
        tmp += int_to_string( n / 10 );

    tmp += n % 10 + 48;

    return tmp;
}

void An::setColor( SDL_Texture* &newTexture, Uint8 red, Uint8 green, Uint8 blue )
{
    SDL_SetTextureColorMod( newTexture, red, green, blue );
}

void An::loadTexture( SDL_Renderer* &renderer, SDL_Texture* &newTexture, std::string path )
{
    SDL_Surface* surface = IMG_Load( path.c_str() );

    if( surface == NULL )
    {
        printf( "Nie wczytano %s Error %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        newTexture = SDL_CreateTextureFromSurface( renderer, surface );

        if( newTexture == NULL )
        {
            printf( "Nie utworzono tekstury z %s Error %s\n", path.c_str(), SDL_GetError() );
        }

        SDL_FreeSurface( surface );

    }
}

void An::render( SDL_Renderer* &renderer, Uint8 red, Uint8 green, Uint8 blue )
{
    off_set ++;

    if( off_set == how_many )
        off_set = 0;



    // wczytywanie
    loadTexture( renderer, texture[ off_set ], "images/0 (" + int_to_string( off_set + 1 ) + ").png" );
    setColor( texture[ off_set ], red, green, blue );
    SDL_RenderCopy( renderer, texture[ off_set ], NULL, NULL );

    SDL_DestroyTexture( texture[ off_set ] );
}

