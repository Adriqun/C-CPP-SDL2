#include "attain.h"

Attain::Attain()
{
	font = NULL;
	
	label = NULL;
	result = NULL;
	
    never = "";
}

Attain::~Attain()
{
    free();
}

void Attain::free()
{
	if( font != NULL )
	{
		delete font;
	}
	
	if( label != NULL )
	{
		delete label;
	}
	
	if( result != NULL )
	{
		delete result;
	}
    
    never = "";
}

bool Attain::load( SDL_Renderer* &renderer, int goal_height )
{
    bool success = true;

    free();

	font = new Font;
    if( !font->load( "data/Chunkfive Ex.ttf", 30 ) )
    {
        success = false;
    }
    else
    {
		label = new Texture;
		if( label != NULL )
		{
			SDL_Color color = { 0x58, 0x58, 0x58 };
			if( !label->loadFromRenderedText( renderer, font->get(), "attain:  ", color ) )
			{
				success = false;
			}
			else
			{
				label->getX() = 10;
				label->getY() = goal_height;

				never = "never";
				color.r = 0xe8;
				color.g = 0x68;
				color.b = 0x50;
				
				result = new Texture;
				if( label != NULL )
				{
					if( !result->loadFromRenderedText( renderer, font->get(), never, color ) )
					{
						success = false;
					}
					else
					{
						result->getX() = label->getR();
						result->getY() = goal_height;
					}
				}
			}
		}
    }

    return success;
}

void Attain::render( SDL_Renderer* &renderer, int screen_width )
{
    label->render( renderer );
    result->render( renderer );

    SDL_SetRenderDrawColor( renderer, 0x58, 0x74, 0x98, 0xFF );
    SDL_RenderDrawLine( renderer, 0, label->getB(), screen_width, label->getB() );
    SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
}
