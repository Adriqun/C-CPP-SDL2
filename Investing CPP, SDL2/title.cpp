#include "title.h"
#include "font.h"

Title::Title()
{
	texture = NULL;
}

Title::~Title()
{
    free();
}

void Title::free()
{
    if( texture != NULL )
	{
		delete texture;
	}
}

bool Title::load( SDL_Renderer* &renderer, int screen_width )
{
    bool success = true;
	
    free();
	
	Font* font = new Font;

    if( !font->load( "data/ShadedLarch_PERSONAL_USE.ttf", 50 ) )
    {
        success = false;
    }
    else
    {
        SDL_Color color = { 0xA4, 0xA4, 0xA4 };
		texture = new Texture;
		if( texture != NULL )
		{
			if( !texture->loadFromRenderedText( renderer, font->get(), "investing", color ) )
			{
				success = false;
			}
			else
			{
				texture->getX() = ( screen_width/2 ) - ( texture->getW()/2 );
				texture->getY() = 0;
			}
		}
    }


    return success;
}

void Title::render( SDL_Renderer* &renderer )
{
    texture->render( renderer );
}

int &Title::getW()
{
    return texture->getW();
}

int &Title::getH()
{
    return texture->getH();
}
