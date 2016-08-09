#include "valuables.h"
#include "font.h"

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
    if( !font->load( "Chunkfive Ex.ttf", 40 ) )
    {
        success = false;
    }
    else
    {
        SDL_Color color;

        // red
        color.r = 0xF4;
        color.g = 0x43;
        color.b = 0x36;
        if( !a.loadFromRenderedText( renderer, font->get(), "+", color ) )
        {
            success = false;
        }
        else
        {
            a.getX() = screen_width/2 - a.getW();
            a.getY() = goal_bar_posY;
        }

        // green
        color.r = 0x8B;
        color.g = 0xC3;
        color.b = 0x4A;
        if( !b.loadFromRenderedText( renderer, font->get(), "-", color ) )
        {
            success = false;
        }
        else
        {
            b.getX() = screen_width/2 + b.getW();
            b.getY() = goal_bar_posY;
        }
    }
	
	delete font;

    return success;
}

void Valuables::render( SDL_Renderer* &renderer )
{
	a.render( renderer );
	b.render( renderer );
}

void Valuables::handle( SDL_Event &event )
{

}
