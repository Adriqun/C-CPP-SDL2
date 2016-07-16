#include "hero.h"
#include <stdio.h>
#include "font.h"


Hero::Hero()
{
    x = 0;
    y = 0;
    vel = 6.0;

    delay = 0;
    offset = 0;

    rect = NULL;

    flip = SDL_FLIP_NONE;

    key = NULL;

    jump_state = 0;
    dead = false;
    alpha = 0;
}

Hero::~Hero()
{
    free();
}

void Hero::free()
{
    x = 0;
    y = 0;

    delay = 0;
    offset = 0;

    texture.free();

    if( rect != NULL )
    {
        for( int i = 0; i < AMOUNT; i++ )
        {
            delete rect[ i ];
            rect[ i ] = NULL;
        }

        delete [] rect;
        rect = NULL;
    }

    flip = SDL_FLIP_NONE;

    key = NULL;

    woosh.free();
    jump_state = 0;
    dead = false;
    alpha = 0;
    score.free();
}


void Hero::idle()
{
    if( !dead )
    {
        // Animation of running
        if( offset > RUN_END * delay )
        {
            offset = RUN_START;
        }
    }
}

void Hero::jump()
{
    if( !dead )
    {
        vel = 0;

        static Uint8 time = 24; // Time for time
        static Uint8 counter = 0;

        // Jump
        if( key[ SDL_SCANCODE_UP ] || key[ SDL_SCANCODE_W ] )
        {
            if( jump_state == 0 )
            {
                jump_state = 1;
            }
        }

        if( jump_state == 1 )
        {
            vel = -13;
            counter ++;
            offset = JUMP * delay;

            if( counter == time )
                jump_state = 2;
        }

        else if( jump_state == 2 )
        {
            counter = 0;
            offset = JUMP * delay;
        }

        y += vel;
    }
}

bool Hero::run()
{
    if( !dead )
    {
        vel = 0;

        // Run
        if( key[ SDL_SCANCODE_LEFT ] || key[ SDL_SCANCODE_A ] )
        {
            vel = -6;
            offset ++;
            flip = SDL_FLIP_HORIZONTAL;
        }

        else if( key[ SDL_SCANCODE_RIGHT ] || key[ SDL_SCANCODE_D ] )
        {
            vel = 6;
            offset ++;
            flip = SDL_FLIP_NONE;
        }

        else
        {
            offset = IDLE * delay;
        }

        x += vel;

        // Max scope
        static Uint16 min = 10;
        static Uint16 max = 600;
        Uint16 a = x + texture.getWidth() / AMOUNT;

        if( a > max || x < min )
        {
            x -= vel;
        }


        // printf( "1.%f\n", vel );

        // If hero is on right edge and running
        return a >= max && ( key[ SDL_SCANCODE_RIGHT ] || key[ SDL_SCANCODE_D ] );
    }

    return false;
}

void Hero::gravitation()
{
    if( !dead )
    {
        // Gravitation
        vel = 6;
        y += vel;
    }
}

void Hero::attack( bool shot )
{
    if( !dead )
    {
        static bool state = false;
        static Uint8 counter = 0;

        // Attack
        if( key[ SDL_SCANCODE_SPACE ] || key[ SDL_SCANCODE_RETURN ] )
        {
            if( !state && !shot )
            {
                woosh.play();
                state = true;
            }
        }

        if( state )
        {
            counter++;

            if( counter < 10 )
            {
                offset = ATTACK * delay;
            }
            else
            {
                counter = 0;
                state = false;
            }
        }
    }
}

bool Hero::getDead( int h )
{
    if( y + texture.getHeight() > h )
        dead = true;

    return dead;
}

void Hero::setDead( bool yes )
{
    if( yes )
        dead = true;
}




void Hero::backX( int back )
{
    if( !dead )
    {
        if( back != -1 )
            x -= vel;

        if( back == 2 )
            dead = true;
    }
}

void Hero::backY( int back )
{
    if( !dead )
    {
        if( back != -1 )
        {
            y -= vel;
            jump_state = 0;
        }

        if( back == 2 )
            dead = true;
    }
}




bool Hero::load( SDL_Renderer* &renderer, SDL_Window* &window )
{
    bool success = true;

    free();

    if( !texture.loadFromFile( renderer, window, "hero/0.png" ) )
    {
        success = false;
    }
    else
    {
        int w, h;
        SDL_GetWindowSize( window, &w, &h );

        x = w / 4;
        y = h - 150 - texture.getHeight();

        delay = 2.0;
        offset = IDLE;

        rect = new SDL_Rect* [ AMOUNT ];
        for( int i = 0; i < AMOUNT; i++ )
        {
            rect[ i ] = new SDL_Rect;
            rect[ i ]->w = texture.getWidth() / AMOUNT;
            rect[ i ]->h = texture.getHeight();
            rect[ i ]->x = i * texture.getWidth() / AMOUNT;
            rect[ i ]->y = 0;
        }

        key = SDL_GetKeyboardState( NULL );
    }

    if( !woosh.load( "hero/woosh.wav", 120 ) )
    {
        success = false;
    }

    Font font;
    if( !font.load( "menu/hulk.ttf", 25 ) )
    {
        success = false;
    }
    else
    {
        SDL_Color color = { 0xFF, 0xFF, 0xFF };

        if( !score.loadFromRenderedText( renderer, font.get(), "+10p", color ) )
        {
            success = false;
        }
    }

    return success;
}

void Hero::render( SDL_Renderer* &renderer )
{
    if( dead )
        offset = DEAD * delay;

    texture.render( renderer, x, y, rect[ static_cast <int> (offset / delay) ], 0.0, NULL, flip );
}


float Hero::getX()
{
    return x;
}

float Hero::getY()
{
    return y;
}

SDL_Rect Hero::getRect()
{
    SDL_Rect rect;
    rect.w = texture.getWidth() / AMOUNT;
    rect.h = texture.getHeight();
    rect.x = x;
    rect.y = y;

    return rect;
}

void Hero::fadeIn()
{
    if( alpha < 250 )
        alpha ++;

    texture.setAlpha( alpha );
}

void Hero::fadeOut()
{
    if( alpha > 0 )
        alpha -= 5;

    texture.setAlpha( alpha );
}

void Hero::render10( SDL_Renderer* &renderer, bool yes )
{
    static int c = 100;
    static Uint8 a = 250;

    if( yes )
    {
        c = 0;
        a = 250;

    }

    if( c < 100 )
    {
        c ++;
        score.render( renderer, x + texture.getWidth() / AMOUNT + 20, y - 50 );
    }

    if( a > 250 )
    {
        score.setAlpha( a );
        a--;
    }

}
