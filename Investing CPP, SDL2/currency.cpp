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
            if( !texture[ GBP ].loadFromRenderedText( renderer, font.get(), "GBP", color ) )
            {
                success = false;
            }
            else
            {
                texture[ GBP ].getX() = screen_width - texture[ GBP ].getW() -5;
                texture[ GBP ].getY() = title_bar_posY;
            }


            if( !texture[ USD ].loadFromRenderedText( renderer, font.get(), "USD", color ) )
            {
                success = false;
            }
            else
            {
                texture[ USD ].getX() = texture[ GBP ].getX() - texture[ USD ].getW() -10;
                texture[ USD ].getY() = title_bar_posY;
            }


            if( !texture[ EUR ].loadFromRenderedText( renderer, font.get(), "EUR", color ) )
            {
                success = false;
            }
            else
            {
                texture[ EUR ].getX() = texture[ USD ].getX() - texture[ EUR ].getW() -10;
                texture[ EUR ].getY() = title_bar_posY;
            }


            if( !texture[ PLN ].loadFromRenderedText( renderer, font.get(), "PLN", color ) )
            {
                success = false;
            }
            else
            {
                texture[ PLN ].getX() = texture[ EUR ].getX() - texture[ PLN ].getW() -10;
                texture[ PLN ].getY() = title_bar_posY;

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
    for( int i = 0; i < nr; i++ )
    {
        if( i != picked )
            texture[ i ].setColor( 255, 255, 255 );
    }
	
	int x = -1;
    int y = -1;
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
		static int buf = -1;
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
					{
						buf = -1;
					}
                }
            }
        }
    }
}

int Currency::get()
{
    return picked;
}
