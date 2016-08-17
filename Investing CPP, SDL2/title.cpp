#include "title.h"
#include "font.h"
#include <stdio.h>

Title::Title()
{
	// empty
}

Title::~Title()
{
    free();
}

void Title::free()
{
	label.free();
	wallpaper.free();
}

bool Title::load( SDL_Renderer* &renderer, int screen_width )
{
    bool success = true;
	
    free();
	
	Font font;
    if( !font.load( "data/ShadedLarch_PERSONAL_USE.ttf", 50 ) )
    {
        success = false;
    }
    else
    {

		SDL_Color color = { 0xA4, 0xA4, 0xA4 };
		if( !label.loadFromRenderedText( renderer, font.get(), "investing", color ) )
		{
			success = false;
		}
		else
		{
			label.getX() = ( screen_width/2 ) - ( label.getW()/2 );
			label.getY() = 0;
		}
    }
	font.free();
	
	if( !wallpaper.createWithColor( renderer, 0x58, 0x74, 0x98, screen_width, label.getH() ) )
	{
		success = false;
	}

    return success;
}

void Title::render( SDL_Renderer* &renderer, int screen_width, int screen_height )
{
	wallpaper.render( renderer );
    label.render( renderer );
	
	//Edges
	SDL_SetRenderDrawColor( renderer, 0x58, 0x74, 0x98, 0xFF );
		
	SDL_RenderDrawLine( renderer, 0, 0, 0, screen_height );
	SDL_RenderDrawLine( renderer, 1, 0, 1, screen_height );
	SDL_RenderDrawLine( renderer, 2, 0, 2, screen_height );
		
	SDL_RenderDrawLine( renderer, screen_width-1, 0, screen_width-1, screen_height );
	SDL_RenderDrawLine( renderer, screen_width-2, 0, screen_width-2, screen_height );
	SDL_RenderDrawLine( renderer, screen_width-3, 0, screen_width-3, screen_height );
		
	SDL_RenderDrawLine( renderer, 0, screen_height-1, screen_width, screen_height-1 );
	SDL_RenderDrawLine( renderer, 0, screen_height-2, screen_width, screen_height-2 );
	SDL_RenderDrawLine( renderer, 0, screen_height-3, screen_width, screen_height-3 );
		
	SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
}

int Title::getH()
{
    return label.getH();
}