#include "menu.h"
#include <stdio.h>

Menu::Menu()
{
    nr = 0;
    key = 0;
    counter = 0;

    x = NULL;
    y = NULL;

    font = NULL;
    texture = NULL;
}

Menu::~Menu()
{
    free();
}


/* Jesli konieczne - zniszcz tablice */
void Menu::free()
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
    key = 0;
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

Uint8 Menu::isClose()
{
    /* Gdy uzytkownik kliknie 'play' */
    if( key == 2 )
    {
        return 1;
    }

    /* Gdy uzytkownik kliknie 'exit' */
    else if( key == 3 )
    {
        return 2;
    }

    return 0;
}



bool Menu::load( SDL_Renderer* &renderer, SDL_Window* &window )
{
    bool success = true;            /* Flaga success */


    free();                         /* Zniszcz tablice i ustaw wskazniki na NULL'a */

    /* Ustaw w i h jako szerokosc i wysokosc okna programu */
    int w, h;
    SDL_GetWindowSize( window, &w, &h );

    /* Wyznacz liczbe elementow w tablicach */
    nr = 6;

    /* Dynamiczne alokowanie pamieci */
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

    /* Wczytaj czcionke */
    font = TTF_OpenFont( "fonts/1.otf", 115 );
    if( font == NULL )
    {
        printf( "Nie wczytano czcionki! Error %s\n", TTF_GetError() );
        success = false;
    }
    else
    {

        /* Ustaw kolor czcionki */
        SDL_Color color;
        color.r = 0x01;
        color.g = 0x01;
        color.b = 0x01;

        /* Kolejno - ustawianie napisow i kolorow czcionki */
        if( !texture[ 0 ].loadFromRenderedText( renderer, font, "collision", color ) )
        {
            printf( "Nie ustawiono tekstu collision\n" );
            success = false;
        }
        else
        {
            x[ 0 ] = 8;
            y[ 0 ] = 8;
        }

        color.r = 0xFF;
        color.g = 0xFF;
        color.b = 0xFF;
        if( !texture[ 1 ].loadFromRenderedText( renderer, font, "detection", color ) )
        {
            printf( "Nie ustawiono tekstu detection\n" );
            success = false;
        }
        else
        {
            x[ 1 ] = x[ 0 ];
            y[ 1 ] = y[ 0 ] + texture[ 1 ].getHeight() - 10;
        }

        color.r = 0x01;
        color.g = 0x01;
        color.b = 0x01;
        if( !texture[ 2 ].loadFromRenderedText( renderer, font, "2d", color ) )
        {
            printf( "Nie ustawiono tekstu 2d\n" );
            success = false;
        }
        else
        {
            x[ 2 ] = x[ 1 ] + texture[ 1 ].getWidth() + 10;
            y[ 2 ] = y[ 1 ];
        }

        color.r = 0xFF;
        color.g = 0x9B;
        color.b = 0x0C;
        if( !texture[ 5 ].loadFromRenderedText( renderer, font, ">", color ) )
        {
            printf( "Nie ustawiono strzalki\n" );
            success = false;
        }
    }

    font = TTF_OpenFont( "fonts/1.otf", 70 );
    if( font == NULL )
    {
        printf( "Nie wczytano czcionki! Error %s\n", TTF_GetError() );
        success = false;
    }
    else
    {
        SDL_Color color = { 0x63, 0x63, 0x63 };
        if( !texture[ 3 ].loadFromRenderedText( renderer, font, "play", color ) )
        {
            printf( "Nie ustawiono tekstu play\n" );
            success = false;
        }
        else
        {
            x[ 3 ] = w / 4;
            y[ 3 ] = h / 2;
            x[ 5 ] = x[ 3 ] - texture[ 5 ].getWidth();
            y[ 5 ] = y[ 3 ] - texture[ 5 ].getHeight() / 5;
        }

        color.r = 0x63;
        color.g = 0x63;
        color.b = 0x63;
        if( !texture[ 4 ].loadFromRenderedText( renderer, font, "exit", color ) )
        {
            printf( "Nie ustawiono tekstu exit\n" );
            success = false;
        }
        else
        {
            x[ 4 ] = w / 4 * 3 - texture[ 4 ].getWidth();
            y[ 4 ] = h / 2 + texture[ 4 ].getHeight();
        }
    }

    return success;
}

void Menu::events( SDL_Event &event )
{
    /* Zabezpieczenie gdyby uzytkownik pomylkowo za szybko kliknal klawisz przed zobaczeniem czegokolwiek */
    if( counter > 200 )
    {
        if( event.key.keysym.sym == SDLK_DOWN ) /* Jesli kliknie klawisz DOWN */
        {
            if( key == 0 )
            {
                /* Ustaw teksture strzalki */
                x[ 5 ] = x[ 4 ] - texture[ 5 ].getWidth();
                y[ 5 ] = y[ 4 ] - texture[ 5 ].getHeight() / 5;
                key = 1;
            }
        }

        else if( event.key.keysym.sym == SDLK_UP ) /* Jesli kliknie klawisz UP */
        {
            if( key == 1 )
            {
                x[ 5 ] = x[ 3 ] - texture[ 5 ].getWidth();
                y[ 5 ] = y[ 3 ] - texture[ 5 ].getHeight() / 5;
                key = 0;
            }
        }

        else if( event.key.keysym.sym == SDLK_RETURN ) /* Jesli kliknie RETURN - Enter */
        {
            /* Gdy key = 0 znaczy to ze strzalka wskazuje na napis 'play' */
            if( key == 0 )
            {
                key = 2;
            }

            /* Gdy key = 1 znaczy to ze strzalka wskazuje na napis 'exit' */
            else if( key == 1 )
            {
                key = 3;
            }
        }
    }
}

void Menu::render( SDL_Renderer* &renderer )
{
    SDL_SetRenderDrawColor( renderer, 0x02, 0x9D, 0xDF, 0x00 );

    if( counter < 254 )
    {
        counter += 2;
    }

    for( Uint8 i = 0; i < nr; i++ )
    {
        texture[ i ].setAlpha( counter );
        texture[ i ].render( renderer, x[ i ], y[ i ] );
    }
}
