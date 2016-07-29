#include "title.h"

Title::Title()
{
    x = 0;
    y = 0;
}

Title::~Title()
{
    free();
}

void Title::free()
{
    x = 0;
    y = 0;
    texture.free();
    font.free();
}

bool Title::load( SDL_Renderer* &renderer, SDL_Window* &window )
{
    bool success = true;

    free();

    if( !font.load( "data/ShadedLarch_PERSONAL_USE.ttf", 50 ) )
    {
        success = false;
    }
    else
    {
        SDL_Color color = { 0xFF, 0xFF, 0xFF };
        if( !texture.loadFromRenderedText( renderer, font.get(), "investing", color ) )
        {
            success = false;
        }
        else
        {
            int w, h;
            SDL_GetWindowSize( window, &w, &h );

            x = w/2 - texture.getWidth()/2;
            y = 0;

            texture.setColor( 0x09, 0x70, 0x54 );
        }
    }


    return success;
}

void Title::render( SDL_Renderer* &renderer )
{
    texture.render( renderer, x, y );
}

void Title::handle( SDL_Event &event )
{
    int posX = -1;
    int posY = -1;
    texture.setColor( 0x09, 0x70, 0x54 );

    if( event.type == SDL_MOUSEMOTION )
    {
        SDL_GetMouseState( &posX, &posY );
        if( posX > x && posX < x + static_cast <int> ( texture.getWidth() ) )
        {
            if( posY > y && posY < y + static_cast <int> ( texture.getHeight() )-10 )
            {
                texture.setColor( 0xFF, 0x99, 0x00 );
            }
        }
    }
}

unsigned Title::getWidth()
{
    return texture.getWidth();
}

unsigned Title::getHeight()
{
    return texture.getHeight();
}
