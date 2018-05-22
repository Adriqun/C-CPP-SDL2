#include "menu.h"
#include <SDL_image.h>

Menu::Menu()
{
    texture = NULL;
    rect = NULL;
    rect = new SDL_Rect;

    rect->x = 0;
    rect->y = 0;
    rect->w = 0;
    rect->h = 0;

    state = 0;
}

Menu::~Menu()
{
    SDL_DestroyTexture( texture );
    texture = NULL;

    delete rect;
    rect = NULL;
}

SDL_Texture* Menu::loadTexture( SDL_Renderer* &renderer, std::string path )
{
    SDL_Surface* surface = IMG_Load( path.c_str() );
    if( surface == NULL )
    {
        SDL_Log( "Nie wczytano %s Error %s\n", path.c_str(), SDL_GetError() );
    }
    else
    {
        SDL_Texture* texture = SDL_CreateTextureFromSurface( renderer, surface );
        SDL_FreeSurface( surface );
        if( texture == NULL )
        {
            SDL_Log( "Nie utworzono tekstury z %s Error %s\n", path.c_str(), SDL_GetError() );
        }
        else
        {
            return texture;
        }
    }
    return NULL;
}

void Menu::load( SDL_Renderer* &renderer, Uint16 w, Uint16 h )
{
    texture = loadTexture( renderer, "menu/0.png" );

    rect->w = w;
    rect->h = h;
}

void Menu::event( SDL_Renderer* &renderer, SDL_Event &e, Uint16 w, Uint16 h )
{
    int x, y;
    if( e.type == SDL_MOUSEBUTTONDOWN )
    {
        // SDL_MOUSEBUTTONDOWN
        x = e.tfinger.x * w;
        y = e.tfinger.y * h;
        SDL_GetMouseState( &x, &y );
    }
    else
    {
        x = -10;
        y = -10;
    }

    if( state == 0 )
    {
        if( x > 146 && x < 146 + 218 && y > 451 && y < 451 + 124 ) // play
        {
            state = 1;
        }
        if( x > 136 && x < 136 + 253 && y > 607 && y < 607 + 102 ) // info
        {
            state = 2;
            SDL_DestroyTexture( texture );
            texture = NULL;
            texture = loadTexture( renderer, "menu/1.png" );
        }
        if( x > 130 && x < 130 + 280 && y > 757 && y < 757 + 104 ) // exit
        {
            state = 3;
        }
    }
    else if( state == 2 ) // info
    {
        if( x > 0 && x < 0 + 303 && y > 0 && y < 0 + 124 )
        {
            state = 0;
            SDL_DestroyTexture( texture );
            texture = NULL;
            texture = loadTexture( renderer, "menu/0.png" );
        }
    }
}

void Menu::render( SDL_Renderer* &renderer )
{
    SDL_RenderCopy( renderer, texture, NULL, rect );
}

int8_t Menu::getFrame()
{
    if( state == 1 )            return 1;
    else if( state == 3 )       return 3;
    else                        return 0;
}




Background::Background()
{
    rect = NULL;
    rect = new SDL_Rect;

    rect->x = 0;
    rect->y = 0;
    rect->w = 0;
    rect->h = 0;

    texture = NULL;
}

Background::~Background()
{
    SDL_DestroyTexture( texture );
    texture = NULL;

    delete rect;
    rect = NULL;
}

SDL_Texture* Background::loadTexture( SDL_Renderer* &renderer, std::string path )
{
    SDL_Surface* surface = IMG_Load( path.c_str() );
    if( surface == NULL )
    {
        SDL_Log( "Nie wczytano %s Error %s\n", path.c_str(), SDL_GetError() );
    }
    else
    {
        SDL_Texture* texture = SDL_CreateTextureFromSurface( renderer, surface );
        SDL_FreeSurface( surface );
        if( texture == NULL )
        {
            SDL_Log( "Nie utworzono tekstury z %s Error %s\n", path.c_str(), SDL_GetError() );
        }
        else
        {
            return texture;
        }
    }
    return NULL;
}

void Background::load( SDL_Renderer* &renderer, Uint16 w, Uint16 h )
{
    texture = loadTexture( renderer, "background/0.png" );

    rect->w = w;
    rect->h = h;
}

void Background::render( SDL_Renderer* &renderer )
{
    SDL_RenderCopy( renderer, texture, NULL, rect );
}
