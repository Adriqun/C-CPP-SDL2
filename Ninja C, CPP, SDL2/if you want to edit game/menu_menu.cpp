#include "menu_menu.h"
#include <stdio.h>


Menu::Menu()
{
    state = 0;
    key = NULL;
    text = NULL;
    image = NULL;

    arrow_nr = 0;
    arrow_offset = 0;
    arrow_rect = NULL;
}

Menu::~Menu()
{
    free();
}

void Menu::free()
{
    state = 0;

    if( text != NULL )
    {
        for( int i = 0; i < AMOUNT_T; i++ )
        {
            text[ i ].free();
        }

        delete [] text;
        text = NULL;
    }

    if( image != NULL )
    {
        for( int i = 0; i < AMOUNT_I; i++ )
        {
            image[ i ].free();
        }

        delete [] image;
        image = NULL;
    }

    if( key != NULL )
    {
        delete key; /* Can make a errors! */
        key = NULL;
    }

    click.free();
    music.free();

    if( arrow_rect != NULL )
    {
        for( int i = 0; i < arrow_nr; i++ )
        {
            delete arrow_rect[ i ];
            arrow_rect[ i ] = NULL;
        }

        delete [] arrow_rect;
        arrow_rect = NULL;

        arrow_nr = 0;
        arrow_offset = 0;
    }
}


bool Menu::load( SDL_Renderer* &renderer, SDL_Window* &window )
{
    bool success = true;

    free();

    image = new Image[ AMOUNT_I ];
    if( image == NULL )
    {
        printf( "Not created array of image\n" );
        success = false;
    }
    else
    {
        // Background
        if( !image[ BACKGROUND ].load( renderer, window, "menu/background.png", 0, 0 ) )
        {
            success = false;
        }

        // Arrow
        if( !image[ ARROW ].load( renderer, window, "hero/0.png", 0, 0 ) )
        {
            success = false;
        }
        else
        {
            arrow_nr = 8;
            arrow_rect = new SDL_Rect* [ arrow_nr ];
            for( int i = 0; i < arrow_nr; i ++ )
            {
                arrow_rect[ i ] = new SDL_Rect;
                arrow_rect[ i ]->x = image[ ARROW ].getWidth() / arrow_nr * i;
                arrow_rect[ i ]->y = 0;
                arrow_rect[ i ]->w = image[ ARROW ].getWidth() / arrow_nr;
                arrow_rect[ i ]->h = image[ ARROW ].getHeight();
            }
        }
    }

    int w, h;
    SDL_GetWindowSize( window, &w, &h );

    text = new Text[ AMOUNT_T ];
    if( text == NULL )
    {
        printf( "Not created array of text\n" );
        success = false;
    }
    else
    {
        // Title
        if( !text[ TITLE ].loadFont( "menu/hulk3d2.ttf", 90, 0x4A, 0x4A, 0x4A ) )
        {
            success = false;
        }
        else if( !text[ TITLE ].createTexture( renderer, "Jump and jump" ) )
        {
            success = false;
        }
        else
        {
            text[ TITLE ].setX( (w / 2) - (text[ TITLE ].getWidth() / 2) );
            text[ TITLE ].setY( 60 );
        }


        // Play
        if( !text[ PLAY ].loadFont( "menu/hulk.ttf", 100, 0x78, 0x78, 0x78 ) )
        {
            success = false;
        }
        else if( !text[ PLAY ].createTexture( renderer, "play" ) )
        {
            success = false;
        }
        else
        {
            text[ PLAY ].setX( (w / 2) - (text[ PLAY ].getWidth() / 2) );
            text[ PLAY ].setY( text[ TITLE ].getY() + text[ PLAY ].getHeight() + 170 );
        }


        // Scores
        if( !text[ SCORES ].loadFont( "menu/hulk.ttf", 100, 0x78, 0x78, 0x78 ) )
        {
            success = false;
        }
        else if( !text[ SCORES ].createTexture( renderer, "scores" ) )
        {
            success = false;
        }
        else
        {
            text[ SCORES ].setX( (w / 2) - (text[ SCORES ].getWidth() / 2) );
            text[ SCORES ].setY( text[ PLAY ].getY() + (text[ SCORES ].getHeight() / 2) + 30 );
        }


        // Scores
        if( !text[ OPTIONS ].loadFont( "menu/hulk.ttf", 100, 0x78, 0x78, 0x78 ) )
        {
            success = false;
        }
        else if( !text[ OPTIONS ].createTexture( renderer, "options" ) )
        {
            success = false;
        }
        else
        {
            text[ OPTIONS ].setX( (w / 2) - (text[ OPTIONS ].getWidth() / 2) );
            text[ OPTIONS ].setY( text[ SCORES ].getY() + (text[ OPTIONS ].getHeight() / 2) + 30 );
        }


        // Exit
        if( !text[ EXIT ].loadFont( "menu/hulk.ttf", 100, 0x78, 0x78, 0x78 ) )
        {
            success = false;
        }
        else if( !text[ EXIT ].createTexture( renderer, "exit" ) )
        {
            success = false;
        }
        else
        {
            text[ EXIT ].setX( (w / 2) - (text[ EXIT ].getWidth() / 2) );
            text[ EXIT ].setY( text[ OPTIONS ].getY() + (text[ EXIT ].getHeight() / 2) + 30 );
        }

        // printf( "Test nr1\n" );
    }

    key = SDL_GetKeyboardState( NULL );

    if( !click.load( "menu/click.wav", 120 ) )
    {
        success = false;
    }

    if( !music.load( "menu/Rayman Legends OST - Moving Ground.mp3", 70 ) )
    {
        success = false;
    }

    return success;
}

void Menu::render( SDL_Renderer* &renderer )
{
    image[ BACKGROUND ].render( renderer );
    image[ ARROW ].render( renderer, NULL, NULL, arrow_rect[ arrow_offset ] );

    if( state < EXIT )
    {
        for( int i = 0; i < AMOUNT_T; i ++ )
        {
            text[ i ].render( renderer );
        }
    }
}

void Menu::play()
{
    music.play();
}


int Menu::getState()
{
    return (state - 4);
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
        image[ ARROW ].setX( text[ state+1 ].getX() - image[ ARROW ].getWidth() - 10 );
        image[ ARROW ].setY( text[ state+1 ].getY() );
    }

    if( state == 0 )        arrow_offset = 6;
    else if( state == 1 )   arrow_offset = 4;
    else if( state == 2 )
    {
        arrow_offset ++;
        if( arrow_offset > 3 )
            arrow_offset = 0;
    }
    else if( state == 3 )   arrow_offset = 7;



    // printf( "%d\n", text[ state + 2 ].getX() - image[ ARROW ].getWidth() - 10 );
    // printf( " y %d\n", text[ state + 2 ].getY() );
}

void Menu::fadeIO( int value )
{
    for( int i = 0; i < AMOUNT_I; i ++ )
    {
        image[ i ].fadeIO( value );
    }


    for( int i = 0; i < AMOUNT_T; i ++ )
    {
        text[ i ].fadeIO( value );
    }
}
