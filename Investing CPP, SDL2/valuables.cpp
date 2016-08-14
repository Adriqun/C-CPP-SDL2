#include "valuables.h"
#include "font.h"
#include <SDL2/SDL.h>

Valuables::Valuables()
{
    // empty
}

Valuables::~Valuables()
{
    free();
}

void Valuables::free()
{
    a.free();
    b.free();
}

bool Valuables::load( SDL_Renderer* &renderer, int goal_bar_posY, int screen_width )
{
    bool success = true;

    free();

    Font* font = new Font;
    if( !font->load( "data/Chunkfive Ex.ttf", 40 ) )
    {
        success = false;
    }
    else
    {
        SDL_Color color;

		// green
        color.r = 0x58;
        color.g = 0x70;
        color.b = 0x58;
        if( !a.loadFromRenderedText( renderer, font->get(), "+", color ) )
        {
            success = false;
        }
        else
        {
            a.getX() = screen_width/2 - a.getW();
            a.getY() = goal_bar_posY;
        }
		
		font->setStyle( 1 );
        // red
        color.r = 0xE8;
        color.g = 0x68;
        color.b = 0x50;
        if( !b.loadFromRenderedText( renderer, font->get(), "-", color ) )
        {
            success = false;
        }
        else
        {
            b.getX() = screen_width/2 + b.getW()-8;
            b.getY() = goal_bar_posY - 4;
        }
    }
	
	delete font;

    return success;
}

void Valuables::render( SDL_Renderer* &renderer )
{
	a.render( renderer );
	b.render( renderer );
	
	SDL_SetRenderDrawColor( renderer, 0x58, 0x74, 0x98, 0xFF );
	
	SDL_RenderDrawLine( renderer, a.getX()-5, a.getY()-2, a.getX()-5, a.getY() + a.getH()-10 );
	SDL_RenderDrawLine( renderer, a.getX() + a.getW() +5, a.getY()-2, a.getX() + a.getW() +5, a.getY() + a.getH()-10 );
	
	SDL_RenderDrawLine( renderer, b.getX() + b.getW() +5, b.getY()+2, b.getX() + b.getW() +5, b.getY() + b.getH()-6 );
	
	SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
}

void Valuables::handle( SDL_Event &event )
{

}
