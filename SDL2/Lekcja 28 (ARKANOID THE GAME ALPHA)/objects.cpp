#include "objects.h"

Floor::Floor()
{
    texture = NULL;
}

Floor::~Floor()
{
    texture = NULL;
}

bool Floor::loadMedia()
{
    texture = loadTexture( "deska.png", rect );

    if( texture == NULL )
    {
        printf( "Blad loadMedia(), texture!\n" );
        return false;
    }

    return true;
}

void Floor::render( SDL_Rect &rectangle )
{
    rect = rectangle;

    SDL_RenderCopyEx( renderer, texture, NULL, &rect, 0, NULL, SDL_FLIP_NONE );
}

void Floor::close()
{
    SDL_DestroyTexture( texture );
}

bool Ball::loadMedia()
{
    texture = loadTexture( "pilka.png", rect );

    if( texture == NULL )
    {
        printf( "Blad loadMedia(), pilka.png!\n" );
        return false;
    }

    return true;
}
