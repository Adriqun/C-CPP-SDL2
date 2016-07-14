#include "hero.h"

Hero::Hero()
{
    texture = NULL;

    rect.w = 0;
    rect.h = 0;

    rect.x = 0;
    rect.y = 540;

    velX = 0;
    velY = 0;

    vel = 7;
    jump = 0;

    counter = 0;
}

Hero::~Hero()
{
    free();
}

void Hero::load( SDL_Renderer* &renderer )
{
    free();

    SDL_Surface* surface = IMG_Load( "hero.png" );

    if( surface == NULL )
    {
        printf( "Nie zaladowano pliku hero.png Error %s\n", IMG_GetError() );
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

void Hero::motion( SDL_Rect _rect )
{
    const Uint8* key = SDL_GetKeyboardState( NULL );

    velX = 0;
    velY = vel;

    if( key[ SDL_SCANCODE_W ] )
    {
        if( jump == 0 && rect.y <= _rect.y )
        {
            counter = 1;
            jump = 1;
        }
    }

    if( key[ SDL_SCANCODE_A ] )         velX = vel * -1;
    else if( key[ SDL_SCANCODE_D ] )    velX = vel;

    if( jump == 1 )
    {
        if( counter < 25 )      velY = vel * -1;
        else
        {
            jump = 2;
            counter = 0;
        }
        counter++;
    }

    else if( jump == 2 )
    {
        if( counter < 30 )      velY = vel;
        else
        {
            jump = 0;
            counter = 0;
        }
        counter++;
    }

    rect.x += velX;
    rect.y += velY;
}

void Hero::render( SDL_Renderer* &renderer )
{
    SDL_RenderCopy( renderer, texture, NULL, &rect );
}

void Hero::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
    SDL_SetTextureColorMod( texture, red, green, blue );
}

void Hero::setBlendMode( SDL_BlendMode blending )
{
    SDL_SetTextureBlendMode( texture, blending );
}

void Hero::setAlpha( Uint8 alpha )
{
    SDL_SetTextureAlphaMod( texture, alpha );
}

SDL_Rect Hero::getRect()
{
    return rect;
}

void Hero::setRect( SDL_Rect _rect )
{
    rect = _rect;
}

void Hero::free()
{
    if( texture == NULL )
    {
        SDL_DestroyTexture( texture );
        texture = NULL;

        rect.w = 0;
        rect.h = 0;
        rect.x = 0;
        rect.y = 0;

        counter = 0;
    }
}

float Hero::getVelX()
{
    return velX;
}

float Hero::getVelY()
{
    return velY;
}
