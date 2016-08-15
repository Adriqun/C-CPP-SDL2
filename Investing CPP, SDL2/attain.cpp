#include "attain.h"

Attain::Attain()
{
    never = "";
}

Attain::~Attain()
{
    free();
}

void Attain::free()
{
	font.free();
	
	label.free();
	result.free();
    
    never = "";
}

bool Attain::load( SDL_Renderer* &renderer, int goal_height )
{
    bool success = true;

    free();

    if( !font.load( "data/Chunkfive Ex.ttf", 30 ) )
    {
        success = false;
    }
    else
    {
		SDL_Color color = { 0x58, 0x58, 0x58 };
		if( !label.loadFromRenderedText( renderer, font.get(), "attain:  ", color ) )
		{
			success = false;
		}
		else
		{
			label.getX() = 10;
			label.getY() = goal_height;

			never = "never";
			color.r = 0xe8;
			color.g = 0x68;
			color.b = 0x50;
				
			if( !result.loadFromRenderedText( renderer, font.get(), never, color ) )
			{
				success = false;
			}
			else
			{
				result.getX() = label.getR();
				result.getY() = goal_height;
			}
		}
    }

    return success;
}

void Attain::render( SDL_Renderer* &renderer, int screen_width )
{
    label.render( renderer );
    result.render( renderer );

    SDL_SetRenderDrawColor( renderer, 0x58, 0x74, 0x98, 0xFF );
    SDL_RenderDrawLine( renderer, 0, label.getB(), screen_width, label.getB() );
    SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
}

int Attain::getB()
{
	return label.getB();
}
