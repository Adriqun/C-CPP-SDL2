#include "objects.h"
#include "keyboard.h"
#include "map_editor.h"

Floor floor;
Ball ball;
Keyboard control;
Map_editor blocks;

bool loadMedia()
{
    if( !floor.loadMedia() )
        return false;

    if( !ball.loadMedia() )
        return false;

    if( !control.load() )
        return false;

    if( !blocks.loadMedia() )
        return false;

    return true;
}

void render()
{
    for( ;; )
    {
        control.mouse();
        if( FRAME == 1 )
        {
            blocks.render_edit_mode( control.point );

            if( control.click == true )
            {
                blocks.saveFile( control.point );
                blocks.loadFile();
            }
        }

        if( FRAME == 1 )
        {
        }

        if( FRAME == 0 )
        {
            control.keys();
            control.collision();

            floor.render( control.floor );
            ball.render( control.ball );
            blocks.render( control.ball, control.state );
        }

        SDL_RenderPresent( renderer );
        SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 255 );
        SDL_RenderClear( renderer );
    }
}

void close()
{
    floor.close();
    ball.close();
    blocks.close();
    shut();
}

int main(int argc, char** argv)
{
    if( !init() )
    {
        printf( "Cos nie tak z init()!\n" );
    }

    else
    {
        if( !loadMedia() )
            printf( "Cos nie tak z loadMedia()!\n" );

        else
            render();
    }

    close();

    return 0;
}
