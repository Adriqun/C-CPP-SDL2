#include "shuriken.h"
#include <stdio.h>

Shuriken::Shuriken()
{
    x = 0;
    y = 0;
    angle = 0.0;
    key = NULL;
    alpha = 0;

    direction = true;
    state = false;
}

Shuriken::~Shuriken()
{
    free();
}

void Shuriken::free()
{
    x = 0;
    y = 0;
    angle = 0.0;
    texture.free();
    key = NULL;
    alpha = 0;

    direction = true;
    state = false;
}


void Shuriken::fadeIn()
{
    if( alpha < 250 )
        alpha ++;

    texture.setAlpha( alpha );
}

void Shuriken::fadeOut()
{
    if( alpha > 0 )
        alpha -= 5;

    texture.setAlpha( alpha );
}


bool Shuriken::control( float x, float y, int screen_width )
{
    if( !state )
    {
        if( key[ SDL_SCANCODE_RIGHT ] || key[ SDL_SCANCODE_D ] ) direction = true;
        if( key[ SDL_SCANCODE_LEFT ] || key[ SDL_SCANCODE_A ] )  direction = false;

        if( key[ SDL_SCANCODE_SPACE ] || key[ SDL_SCANCODE_RETURN ] )
        {
            state = true;
            return false;
        }

        static Uint8 up = 30;
        static Uint8 left = 22;
        static Uint8 right = 65;

        this->y = y + up;
        if( direction )     this->x = x - left;
        else                this->x = x + right;
    }

    if( this->x > screen_width  || this->x + texture.getWidth() < 0 )
    {
        state = false;
    }

    if( state )
    {
        static Uint8 vel = 10;
        static Uint8 degree = 25;

        angle -= degree;
        if( direction ) this->x += vel;
        else            this->x -= vel;
    }

    return state;
}

bool Shuriken::load( SDL_Renderer* &renderer, SDL_Window* &window )
{
    bool success = true;

    free();

    if( !texture.loadFromFile( renderer, window, "hero/shuriken.png" ) )
    {
        success = false;
    }
    else
    {
        key = SDL_GetKeyboardState( NULL );
        if( key == NULL )
        {
            success = false;
        }
    }

    return success;
}

void Shuriken::render( SDL_Renderer* &renderer )
{
    texture.render( renderer, x, y, NULL, angle );
}

SDL_Rect Shuriken::getRect()
{
    // I finish there my coding, that the last function what I written :)
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = texture.getWidth();
    rect.h = texture.getHeight();

    return rect;
}

void Shuriken::setState( bool yes )
{
    if( yes )
        state = false;
}

