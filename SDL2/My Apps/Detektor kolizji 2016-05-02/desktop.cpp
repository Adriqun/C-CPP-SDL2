#include "desktop.h"
#include <stdio.h>
#include <math.h>

Desktop::Desktop()
{
    light = false;
    nr = 0;
    type = RECT;
    value = 0;

    x = NULL;
    y = NULL;

    font = NULL;
    texture = NULL;

    /* Nazwa obiektu */
    name = "desktop";
}

Desktop::~Desktop()
{
    free();
}


/* Usun tablice jesli to konieczne */
void Desktop::free()
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
    }

    light = false;
    nr = 0;
    type = RECT;
    value = 0;

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

bool Desktop::isClose()
{
    /* Jesli uzytkownik kliknal napis 'back' */
    if( type == BACK )
    {
        return true;
    }

    return false;
}



void Desktop::lines( SDL_Renderer* &renderer )
{
    SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
    for( Uint8 i = 1; i < 3; i++ )
    {
        SDL_RenderDrawLine( renderer, 0, 100 + i, 1000, 100 + i );
    }

    /* Rysuj prostokat jesli swiatlo zgaslo i wartosc jest rowna 1 */
    if( value == 1 && light )
    {
        SDL_RenderDrawLine( renderer, x[ 1 ], y[ 1 ], x[ 1 ] + texture[ 1 ].getWidth(), y[ 1 ] );
        SDL_RenderDrawLine( renderer, x[ 1 ], y[ 1 ], x[ 1 ], y[ 1 ]  + texture[ 1 ].getHeight() );
        SDL_RenderDrawLine( renderer, x[ 1 ], y[ 1 ] + texture[ 1 ].getHeight(), x[ 1 ] + texture[ 1 ].getWidth(), y[ 1 ]  + texture[ 1 ].getHeight() );
        SDL_RenderDrawLine( renderer, x[ 1 ] + texture[ 1 ].getWidth(), y[ 1 ], x[ 1 ] + texture[ 1 ].getWidth(), y[ 1 ]  + texture[ 1 ].getHeight() );
    }

    /* Rysuj okrag jesli swiatlo zgaslo i wartosc jest rowna 2 */
    else if( value == 2 && light )
    {
        /* Punkty zerowe x i y oraz promien - radius */
        int x0 = x[ 2 ] + texture[ 2 ].getWidth() / 2;
        int y0 = y[ 2 ] + texture[ 2 ].getHeight() / 2;
        int r = texture[ 2 ].getWidth() / 2;

        for( float angle = 0.0; angle < 360; angle++ )
        {
            int a = x0 - r * cos( angle );
            int b = y0 - r * sin( angle );

            SDL_RenderDrawPoint( renderer, a, b );
        }
    }
}

void Desktop::events( SDL_Event &event )
{
    /* Jesli uzytkownik wcisnal klawisz myszy */
    if( event.type == SDL_MOUSEBUTTONDOWN )
    {
        /* Pobierz punkt kursora */
        SDL_Point point;
        SDL_GetMouseState( &point.x, &point.y );

        for( Uint8 i = BACK; i < nr; i++ )
        {
            if( point.x > x[ i ] && point.x < x[ i ] + texture[ i ].getWidth() )
            {
                if( point.y > y[ i ] && point.y < y[ i ] + texture[ i ].getHeight() )
                {
                    /* Jesli swiatlo juz bylo to zgasnie jesli nie to zaswieci sie */
                    if( i == LIGHT )
                    {
                        light = !light;
                    }

                    /* Mozna zmienic figure jesli swiatlo nie swieci */
                    if( !light )
                    {
                        type = i;
                    }
                }
            }
        }
    }

    /* Gdy nie ma swiatla wyswietlamy odpowiednie kolory */
    if( !light )
    {
        if( type == RECT )              value = 1;
        else if( type == CIRCLE )       value = 2;

        if( value == 1 )
        {
            texture[ RECT ].setColor( 0, 250, 0 );
            texture[ CIRCLE ].setColor( 0xFF, 0xFF, 0xFF );
        }
        else
        {
            texture[ RECT ].setColor( 0xFF, 0xFF, 0xFF );
            texture[ CIRCLE ].setColor( 0, 250, 0 );
        }


        for( Uint8 i = 0; i < nr - 3; i++ )
        {
            texture[ i ].setColor( 0xFF, 0xFF, 0xFF );
        }

        texture[ nr - 1 ].setColor( 0, 250, 0 );
    }

    else
    {
        for( Uint8 i = 0; i < nr - 3; i++ )
        {
            texture[ i ].setColor( 200, 25, 189 );
        }
        texture[ nr - 1 ].setColor( 200, 25, 189 );
        if( value == 1 )        texture[ CIRCLE ].setColor( 200, 25, 189 );
        else                    texture[ RECT ].setColor( 200, 25, 189 );
    }
}



SDL_Rect Desktop::getFigure()
{
    SDL_Rect rect;

    if( value == 1 )
    {
        rect.w = texture[ 1 ].getWidth();   /* Pwwrostokat moze przyjmowac rozna dlugosc i szerokosc */
    }
    else
    {
        rect.w = 0;                         /* 0 informuje inna klase (hero) o tym ze jest to okrag */
    }

    rect.h = texture[ value ].getHeight();
    rect.x = x[ value ];
    rect.y = y[ value ];

    return rect;
}

/* Mowi klasie hero kiedy ma przyjac wartosci startowe */
bool Desktop::reloadHero()
{
    static Uint8 last;

    if( last != type )
    {
        last = type;
        return true;
    }

    return false;
}



void Desktop::render( SDL_Renderer* &renderer )
{
    /* Renderowanie tla */
    texture[ 0 ].render( renderer, x[ 0 ], y[ 0 ] );

    /* Renderowanie rect/circle */
    if( value > 0 && value < 3 )
    {
        texture[ value ].render( renderer, x[ value ], y[ value ] );
    }

    /* Renderowanie napisow, przyciskow */
    for( Uint8 i = 3; i < nr; i++ )
    {
        texture[ i ].render( renderer, x[ i ], y[ i ] );
    }

    /* Renderowanie bialej linii */
    lines( renderer );
}




bool Desktop::load( SDL_Renderer* &renderer, SDL_Window* &window )
{
    bool success = true;                        /* Flaga success */

    /* Tworzenie tablic */
    if( !create() )
    {
        printf( "Blad przy tworzeniu tablic w obiekcie %s!\n", name.c_str() );
        success = false;
    }
    else
    {
        /* Ustawianie tekstur */
        if( !setMedia( renderer, window ) )
        {
            printf( "Blad przy ustawianiu tekstur w obiekcie %s!\n", name.c_str() );
            success = false;
        }

        /* Ustawianie napisow */
        if( !setCaption( renderer, window ) )
        {
            printf( "Blad przy ustawianiu napisow w obiekcie %s!\n", name.c_str() );
            success = false;
        }
    }

    return success;
}

bool Desktop::create( )
{
    bool success = true;                /* Flaga success */

    free();                             /* Czyszczenie zmiennych jesli to konieczne */
    nr = 10;                            /* Ustawianie rozmiaru tablicy */


    /* Tworzenie tablicy x */
    x = new Uint16 [ nr ];
    if( x == NULL )
    {
        printf( "Nie utworzono tablicy x w obiekcie %s!\n", name.c_str() );
        success = false;
    }

    /* Tworzenie tablicy y */
    y = new Uint16 [ nr ];
    if( y == NULL )
    {
        printf( "Nie utworzono tablicy y w obiekcie %s!\n", name.c_str() );
        success = false;
    }

    /* Tworzenie tablicy tekstur */
    texture = new Texture [ nr ];
    if( y == NULL )
    {
        printf( "Nie utworzono tablicy texture w obiekcie %s!\n", name.c_str() );
        success = false;
    }

    return success;
}

bool Desktop::setMedia( SDL_Renderer* &renderer, SDL_Window* &window )
{
    bool success = true;                /* Flaga success */

    /* Pobieranie rozmiaru okna */
    int w, h;
    SDL_GetWindowSize( window, &w, &h );



    /* Wczytywanie pliku desktop.png */
    if( !texture[ 0 ].loadFromFile( renderer, window, "images/desktop.png" ) )
    {
        printf( "Nie wczytano pliku desktop.png w obiekcie %s!\n", name.c_str() );
        success = false;
    }
    else
    {
        x[ 0 ] = 0;
        y[ 0 ] = 0;
    }


    /* Wczytywanie pliku rect.png */
    if( !texture[ 1 ].loadFromFile( renderer, window, "images/rect.png" ) )
    {
        printf( "Nie wczytano pliku rect.png w obiekcie %s!\n", name.c_str() );
        success = false;
    }
    else
    {
        x[ 1 ] = w / 2 - texture[ 1 ].getWidth() / 2;
        y[ 1 ] = h / 2 - texture[ 1 ].getHeight() / 2;
    }


    /* Wczytywanie pliku circle.png */
    if( !texture[ 2 ].loadFromFile( renderer, window, "images/circle.png" ) )
    {
        printf( "Nie wczytano pliku circle.png w obiekcie %s!\n", name.c_str() );
        success = false;
    }
    else
    {
        x[ 2 ] = w / 2 - texture[ 2 ].getWidth() / 2;
        y[ 2 ] = h / 2 - texture[ 2 ].getHeight() / 2;
    }


    /* Wczytywanie pliku button.png */
    for( Uint8 i = nr - 3; i < nr; i++ )
    {
        if( !texture[ i ].loadFromFile( renderer, window, "images/button.png" ) )
        {
            printf( "Nie wczytano obrazu button.png w obiekcie %s!\n", name.c_str() );
            success = false;
        }
        else
        {
            x[ i ] = ( w - texture[ i ].getWidth() * ( nr - i ) ) - 10;
            y[ i ] = 30;
        }
    }

    /* Przypisywanie koloru zielonego */
    texture[ 7 ].setColor( 0, 250, 0 );
    texture[ 9 ].setColor( 0, 250, 0 );

    return success;
}

bool Desktop::setCaption( SDL_Renderer* &renderer, SDL_Window* &window )
{
    bool success = true;                /* Flaga success */

    /* Pobieranie rozmiaru okna */
    int w, h;
    SDL_GetWindowSize( window, &w, &h );



    /* Wczytywanie czcionki */
    font = TTF_OpenFont( "fonts/2.ttf", 50 );
    if( font == NULL )
    {
        printf( "Nie wczytano czcionki w obiekcie %s! Error %s\n", name.c_str(), TTF_GetError() );
        success = false;
    }
    else
    {
        /* Ustawianie koloru czcionki */
        SDL_Color color;
        color.r = 0xFF;
        color.g = 0xFF;
        color.b = 0xFF;

        /* Tworzenie napisu Back */
        if( !texture[ 6 ].loadFromRenderedText( renderer, font, "Back", color ) )
        {
            printf( "Nie ustawiono tekstu Back w obiekcie %s!\n", name.c_str() );
            success = false;
        }
        else
        {
            x[ 6 ] = 20;
            y[ 6 ] = 50 - texture[ 6 ].getHeight() / 2;
        }
    }



    /* Wczytywanie czcionki */
    font = TTF_OpenFont( "fonts/2.ttf", 15 );
    if( font == NULL )
    {
        printf( "Nie wczytano czcionki w obiekcie %s! Error %s\n", name.c_str(), TTF_GetError() );
        success = false;
    }
    else
    {
        /* Ustawianie koloru czcionki */
        SDL_Color color;
        color.r = 0xFF;
        color.g = 0xFF;
        color.b = 0xFF;

        /* Tworzenie napisu Rect */
        if( !texture[ 3 ].loadFromRenderedText( renderer, font, "Rect", color ) )
        {
            printf( "Nie ustawiono tekstu Rect w obiekcie %s!\n", name.c_str() );
            success = false;
        }
        else
        {
            x[ 3 ] = x[ nr - 3 ] + 12;
            y[ 3 ] = 10;
        }


        /* Tworzenie napisu Circle */
        if( !texture[ 4 ].loadFromRenderedText( renderer, font, "Circle", color ) )
        {
            printf( "Nie ustawiono tekstu Circle w obiekcie %s!\n", name.c_str() );
            success = false;
        }
        else
        {
            x[ 4 ] = x[ nr - 2 ] + 12;
            y[ 4 ] = 10;
        }


        /* Tworzenie napisu Light */
        if( !texture[ 5 ].loadFromRenderedText( renderer, font, "Light", color ) )
        {
            printf( "Nie ustawiono tekstu Light w obiekcie %s!\n", name.c_str() );
            success = false;
        }
        else
        {
            x[ 5 ] = x[ nr - 1 ] + 12;
            y[ 5 ] = 10;
        }
    }

    return success;
}
