#include "intro.h"
#include "font.h"
#include <stdio.h>

Intro::Intro()
{
    counter = 0;
    quit = false;

    x = NULL;
    y = NULL;
    texture = NULL;
}

Intro::~Intro()
{
    free();
}


void Intro::free()
{
    counter = 0;
    quit = false;

    if( texture != NULL )
    {
        for( int i = 0; i < nr; i++ )
        {
            texture[ i ].free();
        }

        delete [] texture;
        texture = NULL;
    }

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
    return quit;
}


bool Intro::load( SDL_Renderer* &renderer, SDL_Window* &window )
{
    bool success = true;

    free();

    int w, h;
    SDL_GetWindowSize( window, &w, &h );

    Font* font = new Font;
    if( !font->load( "intro/MaszynaAEG.ttf", 37 ) )
    {
        success = false;
    }
    else
    {
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


        // Our background texture
        if( !texture[ BACKGROUND ].createWithColor( renderer, 0x15, 0x15, 0x1D, w, h ) )
        {
            success = false;
        }
        else
        {
            x[ BACKGROUND ] = 0;
            y[ BACKGROUND ] = 0;
        }


        // Our text on start
        SDL_Color white = { 0xFF, 0xFF, 0xFF };
        if( !texture[ PREVIEW ].loadFromRenderedText( renderer, font->get(), "When nothing makes sense...", white ) )
        {
            success = false;
        }
        else
        {
            x[ PREVIEW ] = (w / 2) - (texture[ PREVIEW ].getWidth() / 2);
            y[ PREVIEW ] = (h / 2) - (texture[ PREVIEW ].getHeight() / 2);
        }


        // Title and image
        SDL_Color green = { 0x70, 0xB7, 0x59 };
        if( !texture[ TITLE ].loadFromRenderedText( renderer, font->get(), "Jump and jump", green ) )
        {
            success = false;
        }
        else if( !texture[ SHURIKEN ].loadFromFile( renderer, window, "intro/shuriken.png" ) )
        {
            success = false;
        }
        else
        {
            x[ TITLE ] =    (w / 2) - (texture[ TITLE ].getWidth() / 2) - 10 - texture[ SHURIKEN ].getWidth();
            y[ TITLE ] =    (h / 2) - (texture[ TITLE ].getHeight() / 2);
            x[ SHURIKEN ] = x[ TITLE ] + texture[ TITLE ].getWidth() + 10;
            y[ SHURIKEN ] = (h / 2) - (texture[ SHURIKEN ].getHeight() / 2);
        }


        // My name and text
        if( !texture[ AUTHOR ].loadFromRenderedText( renderer, font->get(), "Adrian Micha³ek", white ) )
        {
            success = false;
        }
        else if( !texture[ PRODUCED ].loadFromRenderedText( renderer, font->get(), "produced by", green ) )
        {
            success = false;
        }
        else
        {
            x[ AUTHOR ] =   (w / 2) - (texture[ AUTHOR ].getWidth() / 2);
            y[ AUTHOR ] =   (h / 2) - (texture[ AUTHOR ].getHeight() / 2);
            x[ PRODUCED ] = (w / 2) - (texture[ PRODUCED ].getWidth() / 2);
            y[ PRODUCED ] = (h / 2) - (texture[ PRODUCED ].getHeight() / 2) - texture[ AUTHOR ].getHeight() - 10;
        }
    }

    delete font;
    font = NULL;

    return success;
}

void Intro::render( SDL_Renderer* &renderer, int fps )
{
    static float seconds = 1.5;
    static int frames = 3;

    counter ++;

    static Uint8 alpha = 0;

    if( alpha < 250 )
        alpha ++;

    for( int i = 1; i <= frames; i++ )
    {
        if( counter == fps * ( seconds * ( frames - ( frames - i ) ) ) )
        {
            alpha = 0;
        }
    }

    for( int i = BACKGROUND; i < nr; i++ )
    {
        texture[ i ].setAlpha( alpha );
    }

    texture[ BACKGROUND ].render( renderer, x[ BACKGROUND ], y[ BACKGROUND ] );

    if( counter < fps * ( seconds * ( frames - 2 ) ) )
    {
        texture[ PREVIEW ].render( renderer, x[ PREVIEW ], y[ PREVIEW ] );
    }

    else if( counter < fps * ( seconds * ( frames - 1 ) ) )
    {
        texture[ SHURIKEN ].render( renderer, x[ SHURIKEN ], y[ SHURIKEN ] );
        texture[ TITLE ].render( renderer, x[ TITLE ], y[ TITLE ] );
    }

    else if( counter < fps * ( seconds * frames ) )
    {
        texture[ AUTHOR ].render( renderer, x[ AUTHOR ], y[ AUTHOR ] );
        texture[ PRODUCED ].render( renderer, x[ PRODUCED ], y[ PRODUCED ] );
    }

    else
    {
        quit = true;
    }
}
