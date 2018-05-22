#include "power.h"

Power::Power( int hm, std::string p )
{
    texture = NULL;
    srcRect = NULL;

    how_many = hm;
    path = p;

    off_sets = 0;
    counter = 0;
}

Power::~Power()
{
    texture = NULL;
    srcRect = NULL;
}

void Power::loadTexture( SDL_Renderer *&renderer )
{
    SDL_Surface* surface = IMG_Load( path.c_str() );

    if( surface == NULL )
    {
        printf( "Nie wczytano %s Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        texture = SDL_CreateTextureFromSurface( renderer, surface );

        if( texture == NULL )
        {
            printf( "Nie utworzono tekstury z %s Error: %s\n", path.c_str(), SDL_GetError() );
        }
        else
        {
            dstRect.w = surface->h;
            dstRect.h = surface->h;
        }

        SDL_FreeSurface( surface );
    }
}

void Power::load( SDL_Renderer *&renderer )
{
    loadTexture( renderer );
    srcRect = new SDL_Rect [ how_many ];

    for( Uint8 i = 0; i < how_many; i++ )
    {
        srcRect[ i ].w = dstRect.w;
        srcRect[ i ].h = dstRect.h;
        srcRect[ i ].y = 0;
        srcRect[ i ].x = dstRect.w * i;
    }
}

void Power::render( SDL_Renderer *&renderer, bool value, int x, int y )
{
    dstRect.x = x;
    dstRect.y = y;

    SDL_RenderCopy( renderer, texture, &srcRect[ off_sets ], &dstRect );

    if( value == true )
        counter = 1;

    if( counter == 1 )
    {
        off_sets++;
        if( off_sets == how_many - 1 )
        {
            counter = 0;
            off_sets = 0;
        }
    }
}

void Power::close()
{
    SDL_DestroyTexture( texture );
    delete [] srcRect;
}

