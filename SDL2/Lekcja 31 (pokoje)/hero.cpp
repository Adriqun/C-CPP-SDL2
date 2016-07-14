#include "hero.h"

Hero::Hero()
{
    texture = NULL;

    rect.x = 380;
    rect.y = 270;

    velX = 0;
    velY = 0;

    vel = 5;
}

Hero::~Hero()
{
    free();
}

void Hero::free()
{
    if( texture != NULL )
    {
        SDL_DestroyTexture( texture );
        texture = NULL;

        velX = 0;
        velY = 0;
        vel = 3;
    }
}

void Hero::load( SDL_Renderer* &renderer )
{
    free();

    SDL_Surface* surface = IMG_Load( "hero.png" );

    if( surface == NULL )
    {
        printf( "Nie udalo sie wczytac hero.png! Error %s\n", IMG_GetError() );
    }
    else
    {
        texture = SDL_CreateTextureFromSurface( renderer, surface );

        if( texture == NULL )
        {
            printf( "Nie utworzono tekstury z hero.png Error %s\n", SDL_GetError() );
        }
        else
        {
            rect.w = surface->w;
            rect.h = surface->h;
        }

        SDL_FreeSurface( surface );
    }
}

void Hero::render( SDL_Renderer* &renderer )
{
    SDL_RenderCopy( renderer, texture, NULL, &rect );
}

void Hero::motion()
{
    const Uint8* key = SDL_GetKeyboardState( NULL );

    velX = 0;
    velY = 0;

    if( key[ SDL_SCANCODE_UP ] )            velY = vel * -1;
    else if( key[ SDL_SCANCODE_DOWN ] )     velY = vel;
    if( key[ SDL_SCANCODE_LEFT ] )          velX = vel * -1;
    else if( key[ SDL_SCANCODE_RIGHT ] )    velX = vel;

    rect.x += velX;
    rect.y += velY;
}

SDL_Rect Hero::getRect()
{
    return rect;
}
