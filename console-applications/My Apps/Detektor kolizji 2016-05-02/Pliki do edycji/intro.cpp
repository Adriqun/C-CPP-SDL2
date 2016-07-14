#include "intro.h"
#include <stdio.h>

Intro::Intro()
{
    nr = 0;
    counter = 0;

    x = NULL;
    y = NULL;

    font = NULL;
    texture = NULL;
}

Intro::~Intro()
{
    free();
}


/* Jesli dany wskaznik nie wskazuje na NULL'a = tablica do zniszczenia */
void Intro::free()
{
    if( font != NULL )
    {
        font = NULL;
    }

    if( texture != NULL )
    {
        for( Uint8 i = 0; i < nr; i++ )
        {
            texture[ i ].free();
        }

        delete [] texture;
        texture = NULL;
    }

    nr = 0;
    counter = 0;

    if( x != NULL )
    {
        delete [] x;
        x = NULL;
    }

    if( y != NULL )
    {
        delete [] y;
        y = NULL;
    }
}

bool Intro::isClose()
{
    /* Po calkowitym zaniku tekstur zwroc koniec dzialania obiektu */
    if( counter < 1 )
    {
        free();

        return true;
    }

    return false;
}



bool Intro::load( SDL_Renderer* &renderer, SDL_Window* &window )
{
    bool success = true;        /* Flaga success */


    free();                     /* Usun tablice jesli to konieczne */


    /* Ustaw w i h jako szerokosc i wysokosc okna */
    int w, h;
    SDL_GetWindowSize( window, &w, &h );

    /* Wczytaj czcionke */
    font = TTF_OpenFont( "fonts/0.otf", 40 );
    if( font == NULL )
    {
        printf( "Nie wczytano czcionki! Error %s\n", TTF_GetError() );
        success = false;
    }
    else
    {
        /* Ustaw liczby i dynamicznie zaalokuj pamiec - utworz tablice */
        nr = 2;
        counter = 254;

        x = new Uint16 [ nr ];
        if( x == NULL )
        {
            printf( "Nie utworzono tablicy x!\n" );
            success = false;
        }

        y = new Uint16 [ nr ];
        if( y == NULL )
        {
            printf( "Nie utworzono tablicy y!\n" );
            success = false;
        }

        texture = new Texture [ nr ];
        if( y == NULL )
        {
            printf( "Nie utworzono tablicy texture!\n" );
            success = false;
        }

        /* Ustaw kolor czcionki */
        SDL_Color color;
        color.r = 0xFB;
        color.g = 0x54;
        color.b = 0x4D;

        /* Stworz napis */
        if( !texture[ 0 ].loadFromRenderedText( renderer, font, "Adrian Michalek", color ) )
        {
            printf( "Nie ustawiono tekstu Adrian Michalek\n" );
            success = false;
        }
        else
        {
            /* Ustaw wspolrzedne tego napisu */
            x[ 0 ] = w / 2 - texture[ 0 ].getWidth() / 2;
            y[ 0 ] = h / 2 - texture[ 0 ].getHeight() / 2;
        }

        color.r = 0xF8;
        color.g = 0xF8;
        color.b = 0xF8;

        if( !texture[ 1 ].loadFromRenderedText( renderer, font, "author:", color ) )
        {
            printf( "Nie ustawiono tekstu author:\n" );
            success = false;
        }
        else
        {
            x[ 1 ] = w / 2 - texture[ 1 ].getWidth() / 2;
            y[ 1 ] = h / 2 - texture[ 1 ].getHeight() / 2 - 10 - texture[ 0 ].getHeight();
        }
    }

    /* Jesli wszystko zakonczylo sie powodzeniem zwroc prawde */
    return success;
}

void Intro::render( SDL_Renderer* &renderer )
{
    /* Odejmuj dopoki counter > 1 ( funkcja - isClose() ) */
    counter -= 2;

    SDL_SetRenderDrawColor( renderer, 0x1C, 0x20, 0x2B, 0x00 );

    for( Uint8 i = 0; i < nr; i++ )
    {
        texture[ i ].setAlpha( counter );
        texture[ i ].render( renderer, x[ i ], y[ i ] );
    }
}
