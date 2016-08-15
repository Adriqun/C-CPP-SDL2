#include "currency.h"
#include "font.h"

Currency::Currency()
{
    nr = 0;

    texture = NULL;
    picked = 0;
}

Currency::~Currency()
{
    free();
}

void Currency::free()
{
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

    picked = 0;
    click.free();
    focus.free();
}

bool Currency::load( SDL_Renderer* &renderer, int title_bar_posY, int screen_width )
{
    bool success = true;

    free();
	
	Font font;
    if( !font.load( "data/Chunkfive Ex.ttf", 30 ) )
    {
        success = false;
    }
    else
    {
        nr = 4;

        texture = new Texture [ nr ];
        if( texture == NULL )
        {
            printf( "Not created array of Texture!\n" );
            success = false;
        }
        else
        {
            SDL_Color color = { 0x58, 0x74, 0x98 };

            if( !texture[ 0 ].loadFromRenderedText( renderer, font.get(), "GBP", color ) )
            {
                success = false;
            }
            else
            {
                texture[ 0 ].getX() = screen_width - texture[ 0 ].getW() -5;
                texture[ 0 ].getY() = title_bar_posY;
            }


            if( !texture[ 1 ].loadFromRenderedText( renderer, font.get(), "USD", color ) )
            {
                success = false;
            }
            else
            {
                texture[ 1 ].getX() = texture[ 0 ].getX() - texture[ 1 ].getW() -10;
                texture[ 1 ].getY() = title_bar_posY;
            }


            if( !texture[ 2 ].loadFromRenderedText( renderer, font.get(), "EUR", color ) )
            {
                success = false;
            }
            else
            {
                texture[ 2 ].getX() = texture[ 1 ].getX() - texture[ 2 ].getW() -10;
                texture[ 2 ].getY() = title_bar_posY;
            }


            if( !texture[ 3 ].loadFromRenderedText( renderer, font.get(), "PLN", color ) )
            {
                success = false;
            }
            else
            {
                texture[ 3 ].getX() = texture[ 2 ].getX() - texture[ 3 ].getW() -10;
                texture[ 3 ].getY() = title_bar_posY;

                picked = 3;
                texture[ picked ].setColor( 200, 200, 200 );
            }
        }
    }
	font.free();

    if( !click.load( "data/click.wav", 40 ) )
    {
        success = false;
    }

    if( !focus.load( "data/focus.wav", 10 ) )
    {
        success = false;
    }

    return success;
}

void Currency::render( SDL_Renderer* &renderer )
{
    SDL_SetRenderDrawColor( renderer, 0x58, 0x74, 0x98, 0xFF );

    for( int i = 0; i < nr; i ++ )
    {
        SDL_RenderDrawLine( renderer, texture[ i ].getX()-5, texture[ i ].getY()-10, texture[ i ].getX()-5, texture[ i ].getY() + texture[ i ].getH() +3 );
    }

    SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );


    for( int i = 0; i < nr; i ++ )
    {
        texture[ i ].render( renderer );
    }
}

void Currency::handle( SDL_Event &event )
{
    static int buf = -1;
    int x = -1;
    int y = -1;

    for( int i = 0; i < nr; i++ )
    {
        if( i != picked )
            texture[ i ].setColor( 255, 255, 255 );
    }

    if( event.type == SDL_MOUSEBUTTONDOWN )
    {
        SDL_GetMouseState( &x, &y );

        for( int i = 0; i < nr; i++ )
        {
                if( x > texture[ i ].getX() && x < texture[ i ].getX() + texture[ i ].getW() )
                {
                    if( y > texture[ i ].getY() && y < texture[ i ].getY() + texture[ i ].getH() )
                    {
                            texture[ i ].setColor( 200, 200, 200 );
                            picked = i;
                            click.play();
                    }
                }
        }
    }

    else if( event.type == SDL_MOUSEMOTION )
    {
        SDL_GetMouseState( &x, &y );

        for( int i = 0; i < nr; i++ )
        {
            if( i != picked )
            {
                if( x > texture[ i ].getX() && x < texture[ i ].getX() + texture[ i ].getW() )
                {
                    if( y > texture[ i ].getY() && y < texture[ i ].getY() + texture[ i ].getH() )
                    {
                        texture[ i ].setColor( 200, 200, 200 );

                        if( buf != i )
                        {
                            buf = i;
                            focus.play();
                        }
                    }
                    else
                        buf = -1;
                }
            }
        }
    }
}

int Currency::get()
{
    return picked;
}
