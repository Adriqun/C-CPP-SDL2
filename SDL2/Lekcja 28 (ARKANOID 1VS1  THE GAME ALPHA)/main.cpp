#include "global.h"
#include "objects.h"
#include "control.h"
#include "intro.h"

Control control;
Board board_one;
Board board_two;
Background background;
Ball ball;
Button play, exit, reset, menu;

bool load()
{
    if( !control.load() )
        return false;

    if( !board_one.load( "images/deska2.png" ) )
        return false;

    if( !board_two.load( "images/deska1.png" ) )
        return false;

    if( !background.load( "images/tlo.png" ) )
        return false;

    if( !ball.load( "images/pilka.png" ) )
        return false;

    return true;
}

void close()
{
    board_one.close();
    board_two.close();
    ball.close();
}

void render()
{
    for( ;; )
    {
        control.mouse_control();
        background.render();

        if( FRAME == 0 )
        {
            play.render( control.play );
            exit.render( control.exit );

            if( FRAME == 1 )
            {
                close();
                load();
            }
        }

        if( FRAME == 1 )
        {
            control.collision();
            control.ball_control();
            control.keys_control();

            board_one.render( control.board_one );
            board_two.render( control.board_two );
            ball.render( control.ball );
        }

        if( FRAME == 2 )
        {
            reset.render( control.play );
            menu.render( control.exit );

            if( FRAME != 2 )
            {
                close();
                load();
            }
        }

        SDL_Delay( 2 );
        SDL_RenderPresent( renderer );
        SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 255 );
        SDL_RenderClear( renderer );
    }
}

int main( int argc, char** argv )
{
    if( !init() )
    {
        printf( "Cos nie tak z init()!\n" );
    }
    else
    {
        if( !load() )
        {
            printf( "Cos nie tak z load()!\n" );
        }
        else
        {
            play.load( "images/play.png" );
            exit.load( "images/exit.png" );
            reset.load( "images/reset.png" );
            menu.load( "images/menu.png" );

            render();
        }
    }
    close();
    background.close();
    SDL_Quit();
    IMG_Quit();

    return 0;
}
