#include "scores.h"
#include <stdio.h>
#include <fstream>
#include "font.h"

using namespace std;

Scores::Scores()
{
    nr = 0;

    x = NULL;
    y = NULL;
    texture = NULL;
}

Scores::~Scores()
{
    free();
}

void Scores::free()
{
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
        nr = 0;
    }
}


bool Scores::load( SDL_Renderer* &renderer, SDL_Window* &window )
{
    bool success = true;

    free();

    ifstream file;
    file.open( "menu/scores.txt" );
    if( file.bad() )
    {
        success = false;
    }
    else
    {
        nr = 11;

        string* line = new string [ nr-1 ];

        int counter = 0;
        while( counter < nr-1 )
        {
            getline( file, line[ counter ] );
            line[ counter ] += " scores";
            counter ++;
        }

        int w, h;
        SDL_GetWindowSize( window, &w, &h );

        Font* font = new Font;
        if( !font->load( "menu/hulk.ttf", 70 ) )
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

            // Loading scores
            SDL_Color gold = { 0xFF, 0xDF, 0x62 };
            if( !texture[ 0 ].loadFromRenderedText( renderer, font->get(), line[ 0 ], gold ) )
            {
                success = false;
            }
            else
            {
                x[ 0 ] = (w / 2) - (texture[ 0 ].getWidth() / 2);
            }

            SDL_Color silver = { 0xBC, 0xBC, 0xBC };
            if( !texture[ 1 ].loadFromRenderedText( renderer, font->get(), line[ 1 ], silver ) )
            {
                success = false;
            }
            else
            {
                x[ 1 ] = (w / 2) - (texture[ 1 ].getWidth() / 2);
            }

            SDL_Color bronze = { 0xE4, 0x90, 0x67 };
            if( !texture[ 2 ].loadFromRenderedText( renderer, font->get(), line[ 2 ], bronze ) )
            {
                success = false;
            }
            else
            {
                x[ 2 ] = (w / 2) - (texture[ 2 ].getWidth() / 2);
            }


            // continue Loading scores
            SDL_Color gray = { 0x78, 0x78, 0x78 };
            for( int i = 3; i < nr-1; i++ )
            {
                if( !texture[ i ].loadFromRenderedText( renderer, font->get(), line[ i ], gray ) )
                {
                    success = false;
                }

                x[ i ] = (w / 2) - (texture[ i ].getWidth() / 2);
            }

            delete [] line;
            line = NULL;


            y[ 0 ] = 80;
            for( int i = 1; i < nr-1; i++ )
            {
                y[ i ] = y[ i - 1 ] + (texture[ i - 1 ].getHeight() / 2) + 25;
            }


            delete font;
            font = NULL;

            // Our background texture
            if( !texture[ nr-1 ].loadFromFile( renderer, window, "menu/background.png" ) )
            {
                success = false;
            }
            else
            {
                y[ nr-1 ] = 0;
                x[ nr-1 ] = 0;
            }
        }
    }

    file.close();

    return success;
}

void Scores::render( SDL_Renderer* &renderer )
{
    for( int i = nr-1; i >= 0; i-- )
    {
        texture[ i ].render( renderer, x[ i ], y[ i ] );
    }
}
