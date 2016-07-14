#include "objects.h"

Board::Board()
{
    texture = NULL;
}

Board::~Board()
{
    texture = NULL;
}

bool Board::load( string path )
{
    texture = loadTexture( path , rect );

    if( texture == NULL )
    {
        printf( "Nie wczytano deska.png!\n" );
        return false;
    }

    return true;
}

void Board::render( SDL_Rect &rectangle )
{
    rect.x = rectangle.x;
    rect.y = rectangle.y;

    SDL_RenderCopy( renderer, texture, NULL, &rect );
}

void Board::close()
{
    SDL_DestroyTexture( texture );
}

void Background::render()
{
    SDL_RenderCopy( renderer, texture, NULL, NULL );
}
