#include "menu_scores.h"
#include <stdio.h>
#include <fstream>

Scores::Scores()
{
    nr = 0;
    text = NULL;
}

Scores::~Scores()
{
    free();
}

void Scores::free()
{
    if( text != NULL )
    {
        for( int i = 0; i < nr; i++ )
        {
            text[ i ].free();
        }

        delete [] text;
        text = NULL;

        nr = 0;
    }
}

bool Scores::load( SDL_Renderer* &renderer,  SDL_Window* &window )
{
    bool success = true;

    free();

    int w, h;
    SDL_GetWindowSize( window, &w, &h );

    nr = 10;
    text = new Text [ nr ];
    if( text == NULL )
    {
        printf( "Not created array of text\n" );
        success = false;
    }
    else
    {
        // Loading scores from file
        ifstream file;
        file.open( "menu/scores.txt" );
        if( file.bad() )
        {
            success = false;
        }
        else
        {
            string* line = new string [ nr ];

            int counter = 0;

            while( counter < nr )
            {
                getline( file, line[ counter ] );
                line[ counter ] += " scores";
                counter ++;
            }

            // printf( "Test nr2\n" );

            // Gold score
            if( !text[ 0 ].loadFont( "menu/hulk.ttf", 70, 0xFF, 0xDF, 0x62 ) )
            {
                success = false;
            }
            else if( !text[ 0 ].createTexture( renderer, line[ 0 ] ) )
            {
                success = false;
            }
            else
            {
                text[ 0 ].setX( (w / 2) - (text[ 0 ].getWidth() / 2) );
            }


            // Silver score
            if( !text[ 1 ].loadFont( "menu/hulk.ttf", 70, 0xBC, 0xBC, 0xBC ) )
            {
                success = false;
            }
            else if( !text[ 1 ].createTexture( renderer, line[ 1 ].c_str() ) )
            {
                success = false;
            }
            else
            {
                text[ 1 ].setX( (w / 2) - (text[ 1 ].getWidth() / 2) );
            }


            // Bronze score
            if( !text[ 2 ].loadFont( "menu/hulk.ttf", 70, 0xE4, 0x90, 0x67 ) )
            {
                success = false;
            }
            else if( !text[ 2 ].createTexture( renderer, line[ 2 ].c_str() ) )
            {
                success = false;
            }
            else
            {
                text[ 2 ].setX( (w / 2) - (text[ 2 ].getWidth() / 2) );
            }


            // Continue
            for( int i = 3; i < nr; i++ )
            {
                if( !text[ i ].loadFont( "menu/hulk.ttf", 70, 0x78, 0x78, 0x78 ) )
                {
                    success = false;
                }
                else if( !text[ i ].createTexture( renderer, line[ i ] ) )
                {
                    success = false;
                }
                else
                {
                    text[ i ].setX( (w / 2) - (text[ i ].getWidth() / 2) );
                }
            }

            delete [] line;
            line = NULL;


            text[ 0 ].setY( 80 );
            for( int i = 1; i < nr; i++ )
            {
                text[ i ].setY( text[ i - 1 ].getY() + (text[ i - 1 ].getHeight() / 2) + 25 );
            }

        }

        file.close();
    }

    return success;
}

void Scores::render( SDL_Renderer* &renderer )
{
    for( int i = 0; i < nr; i++ )
    {
        text[ i ].render( renderer );
    }
}

void Scores::fadeIO( int value )
{
    for( int i = 0; i < nr; i++ )
    {
        text[ i ].fadeIO( value );
    }
}
