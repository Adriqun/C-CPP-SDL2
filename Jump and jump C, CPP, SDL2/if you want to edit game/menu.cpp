#include "menu.h"
#include "font.h"
#include <stdio.h>

Menu::Menu()
{
    state = 0;
    alpha = 0;

    x = NULL;
    y = NULL;
    texture = NULL;
    key = NULL;
}

Menu::~Menu()
{
    free();
}

void Menu::free()
{
    state = 0;
    alpha = 0;

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

    if( texture != NULL )
    {
        for( int i = 0; i < nr; i++ )
        {
            texture[ i ].free();
        }

        delete [] texture;
        texture = NULL;
    }

    if( key != NULL )
    {
        delete key; /* Can make a errors! */
        key = NULL;
    }

    click.free();
    music.free();
}


bool Menu::load( SDL_Renderer* &renderer, SDL_Window* &window )
{
    bool success = true;

    free();

    int w, h;
    SDL_GetWindowSize( window, &w, &h );

    x = new int [ nr ];
    if( x == NULL )
    {
        printf( "Not created array of int\n" );
        success = false;
    }

    y = new int [ nr ];
    if( y == NULL )
    {
        printf( "Not created array of int\n" );
        success = false;
    }

    texture = new Texture[ nr ];
    if( texture == NULL )
    {
        printf( "Not created array of texture\n" );
        success = false;
    }

    // Background
    if( !texture[ BACKGROUND ].loadFromFile( renderer, window, "menu/background.png" ) )
    {
        success = false;
    }
    else
    {
        x[ BACKGROUND ] = 0;
        y[ BACKGROUND ] = 0;
    }

    Font* font = new Font;
    if( !font->load( "menu/hulk3d2.ttf", 90 ) )
    {
        success = false;
    }
    else
    {
        // Title
        SDL_Color gray = { 0x4A, 0x4A, 0x4A };
        if( !texture[ TITLE ].loadFromRenderedText( renderer, font->get(), "Jump and jump", gray ) )
        {
            success = false;
        }
        else
        {
            x[ TITLE ] = (w / 2) - (texture[ TITLE ].getWidth() / 2);
            y[ TITLE ] = 60;
        }
    }

    delete font;

    font = new Font;
    if( !font->load( "menu/hulk.ttf", 100 ) )
    {
        success = false;
    }
    else
    {
        //Play
        SDL_Color light_gray = { 0x78, 0x78, 0x78 };
        if( !texture[ PLAY ].loadFromRenderedText( renderer, font->get(), "play", light_gray ) )
        {
            success = false;
        }
        else
        {
            x[ PLAY ] = (w / 2) - (texture[ PLAY ].getWidth() / 2);
            y[ PLAY ] = y[ TITLE ] + texture[ PLAY ].getHeight() + 170;
        }


        //Scores
        if( !texture[ SCORES ].loadFromRenderedText( renderer, font->get(), "scores", light_gray ) )
        {
            success = false;
        }
        else
        {
            x[ SCORES ] = (w / 2) - (texture[ SCORES ].getWidth() / 2);
            y[ SCORES ] = y[ PLAY ] + (texture[ SCORES ].getHeight() / 2) + 30;
        }


        // Options
        if( !texture[ OPTIONS ].loadFromRenderedText( renderer, font->get(), "options", light_gray ) )
        {
            success = false;
        }
        else
        {
            x[ OPTIONS ] = (w / 2) - (texture[ OPTIONS ].getWidth() / 2);
            y[ OPTIONS ] = y[ SCORES ] + (texture[ OPTIONS ].getHeight() / 2) + 30;
        }


        //Exit
        if( !texture[ EXIT ].loadFromRenderedText( renderer, font->get(), "exit", light_gray ) )
        {
            success = false;
        }
        else
        {
            x[ EXIT ] = (w / 2) - (texture[ EXIT ].getWidth() / 2);
            y[ EXIT ] = y[ OPTIONS ] + (texture[ EXIT ].getHeight() / 2) + 30;
        }
    }

    //Arrow
    if( !texture[ ARROW ].loadFromFile( renderer, window, "menu/arrow.png" ) )
    {
        success = false;
    }
    else
    {
        x[ ARROW ] = x[ PLAY ] - texture[ ARROW ].getWidth() - 10;
        y[ ARROW ] = y[ PLAY ];
    }

    delete font;

    key = SDL_GetKeyboardState( NULL );

    if( !click.load( "menu/click.wav", 120 ) )
    {
        success = false;
    }

    if( !music.load( "menu/Rayman Legends OST - The Swamp Whistler.mp3", 70 ) )
    {
        success = false;
    }

    return success;
}

void Menu::render( SDL_Renderer* &renderer )
{
    if( alpha < 250 && state != 4 )
    {
        alpha ++;
    }

    for( int i = 0; i < nr; i ++ )
    {
        texture[ i ].setAlpha( alpha );
        texture[ i ].render( renderer, x[ i ], y[ i ] );
    }

    music.play();
}


int Menu::getState()
{
    if( state != 4 )
        return state - 4;
    else
    {
        alpha --;
        if( alpha < 0 )
            return 0;

        return -5;
    }
}

void Menu::control()
{
    static const int max = 10;
    static int delay = 0;

    if( delay < max )
    {
        delay ++;
    }
    else if( delay == max )
    {
        if( key[ SDL_SCANCODE_DOWN ] )
        {
            if( state < 3 )
            {
                click.play();
                state ++;
                delay = 0;
            }
        }
        else if( key[ SDL_SCANCODE_UP ] )
        {
            if( state > 0 )
            {
                click.play();
                state --;
                delay = 0;
            }
        }
        else if( key[ SDL_SCANCODE_RETURN ] )
        {
            if( state < 4 )
                state += 4;
            else
                state -= 4;

            click.play();
            delay = 0;
        }
    }

    // Setting arrow
    if( state != 4 )
    {
        x[ ARROW ] = x[ state + 2 ] - texture[ ARROW ].getWidth() - 10;
        y[ ARROW ] = y[ state + 2 ];
    }
}

