#include "room.h"

Room::Room()
{
    for( Uint8 i = 0; i < 4; i++ )
        texture[ i ] = NULL;

    counter = 0;
}

Room::~Room()
{
    free();
}

void Room::free()
{
    for( Uint8 i = 0; i < 4; i++ )
        if( texture[ i ] != NULL )
        {
            SDL_DestroyTexture( texture[ i ] );
            texture[ i ] = NULL;
        }
}

SDL_Texture* Room::loadTexture( SDL_Renderer* &renderer, std::string path )
{
    SDL_Surface* surface = IMG_Load( path.c_str() );
    SDL_Texture* newTexture = NULL;

    if( surface == NULL )
    {
        printf( "Nie wczytano %s Error %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        newTexture = SDL_CreateTextureFromSurface( renderer, surface );

        if( newTexture == NULL )
        {
            printf( "Nie utworzno tekstury z %s Error %s\n", path.c_str(), SDL_GetError() );
        }

        SDL_FreeSurface( surface );
    }

    return newTexture;
}

void Room::load( SDL_Renderer* &renderer )
{
    texture[ 0 ] = loadTexture( renderer, "pokoja.png" );
    texture[ 1 ] = loadTexture( renderer, "pokojb.png" );
    texture[ 2 ] = loadTexture( renderer, "pokojc.png" );
    texture[ 3 ] = loadTexture( renderer, "pokojd.png" );

    rect[ 0 ].x = 350;
    rect[ 0 ].y = 0;
    rect[ 0 ].w = 100;
    rect[ 0 ].h = 30;

    rect[ 1 ].x = 770;
    rect[ 1 ].y = 200;
    rect[ 1 ].w = 30;
    rect[ 1 ].h = 100;

    rect[ 2 ].x = 350;
    rect[ 2 ].y = 570;
    rect[ 2 ].w = 100;
    rect[ 2 ].h = 30;

    rect[ 3 ].x = 0;
    rect[ 3 ].y = 200;
    rect[ 3 ].w = 30;
    rect[ 3 ].h = 100;
}

void Room::render( SDL_Renderer* &renderer, Uint8 visible )
{

    SDL_RenderCopy( renderer, texture[ visible ], NULL, NULL );

    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );

    if( visible != 4 )
        SDL_RenderDrawRect( renderer, &rect[ visible ] );
    else
    {
        for( Uint8 i = 0; i < 4; i++ )
            SDL_RenderDrawRect( renderer, &rect[ i ] );
    }

    SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 255 );
}

SDL_Rect Room::getRect()
{
    counter ++;

    if( counter == 4 )
        counter = 0;

    return rect[ counter ];
}
