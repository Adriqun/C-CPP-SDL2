#include "hero.h"
#include <stdio.h>
#include <math.h>

Hero::Hero()
{
    speed = 0;
    x = 0;
    y = 0;

    key = NULL;
}

Hero::~Hero()
{
    free();
}


bool Hero::checkCollision( SDL_Rect rect )
{
    /* Jesli mamy doczynienia z prostokatem */
    if( rect.w != 0 )
    {
        /* W prosty sposob sprawdzamy czy wystapila kolizja */
        if( y + texture.getHeight() <= rect.y )
            return false;

        if( y >= rect.y + rect.h )
            return false;

        if( x + texture.getWidth() <= rect.x )
            return false;

        if( x >=  rect.x + rect.w )
            return false;
    }

    /* Jesli nasze rect.w (szerokosc) = 0 oznacza to ze obiekt jest kolem, i przyjmujemy inny system */
    else
    {
        int r = rect.h / 2;
        int dx = ( rect.x + rect.h / 2 ) - ( x + texture.getWidth() / 2 );
        int dy = ( rect.y + rect.h / 2 ) - ( y + texture.getHeight() / 2 );

        int distance = sqrt( dx * dx + dy * dy );

        /* Obliczamy dystans z Pitagorasa i sprawdzamy czy jest on wiekszy jesli nie to wystapila kolizja */
        if( distance > r + texture.getWidth() / 2 )
        {
            return false;
        }
    }

    return true;
}

/* Czyszczenie zmiennych jesli to konieczne */
void Hero::free()
{
    texture.free();
    key = NULL;

    speed = 0;
    x = 0;
    y = 0;
}

void Hero::motion( SDL_Rect rect )
{
    /* Dla kazdego warunku - jesli uzytkownik kliknal LEFT to postac porusza sie w lewo z okreslona predkoscia, itd... */
    if( key[ SDL_SCANCODE_LEFT ] )
    {
        if( x > 0 )
        {
            x -= speed;
        }

    /* Dla kazdego warunku - jesli wystapila kolizja to cofa postac jeszcze przed wyrenderowaniem calej sytuacji */
        if( checkCollision( rect ) )
        {
            x += speed;
        }
    }

    else if( key[ SDL_SCANCODE_RIGHT ] )
    {
        if( x < 800 - texture.getWidth() )
        {
            x += speed;
        }

        if( checkCollision( rect ) )
        {
            x -= speed;
        }
    }

    if( key[ SDL_SCANCODE_UP ] )
    {
        if( y > 104 )
        {
            y -= speed;
        }

        if( checkCollision( rect ) )
        {
            y += speed;
        }
    }

    else if( key[ SDL_SCANCODE_DOWN ] )
    {
        if( y < 600 - texture.getHeight() )
        {
            y += speed;
        }

        if( checkCollision( rect ) )
        {
            y -= speed;
        }
    }
}



bool Hero::load( SDL_Renderer* &renderer, SDL_Window* &window )
{
    bool success = true;            /* Flaga success */

    free();

    /* Wczytywanie tekstury */
    if( !texture.loadFromFile( renderer, window, "images/hero.png" ) )
    {
        printf( "Nie wczytano tekstury dla obiektu Hero!\n" );
        success = false;
    }
    else
    {
        /* Ustawianie predkosci, polozenia x i y, oraz przypisywanie zmiennej Uint8* */
        key = SDL_GetKeyboardState( NULL );
        x = 15;
        y = 115;
        speed = 3.5;
    }

    return success;
}

void Hero::render( SDL_Renderer* &renderer )
{
    /* Renderowanie tekstury */
    texture.render( renderer, x, y );
}
