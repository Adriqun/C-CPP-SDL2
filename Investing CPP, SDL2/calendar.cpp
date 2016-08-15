#include "calendar.h"
#include "font.h"

Calendar::Calendar()
{
	nr = 0;
	texture = NULL:
	type = 0;
}

Calendar::~Calendar()
{
	free();
}

void Calendar::free()
{
	if( texture != NULL )
	{
		for( int i = 0; i < nr; i ++ )
		{
			texture[ i ].free();
		}
		
		delete [] texture;
		texture = NULL;
		nr = 0;
	}
	
	type = 0;
}

	
bool Calendar::load( SDL_Renderer* &renderer )
{
	register bool success = true;
	
	Font font;
	if( !font.load( "data/Chunkfive Ex.ttf", 30 ) )
	{
		success = false;
	}
	else
	{
		nr = 5;
		texture = new Texture [ nr ];
		
		if( texture != NULL )
		{
			if( !texture[ 0 ].createWithColor( renderer, 0xFF, 0xFF, 0xFF, 200, 200 ) )
			{
				success = false;
			}
			
			SDL_Color color = { 0x58, 0x74, 0x98 };
			
			if( !texture[ 1 ].loadFromRenderedText( renderer, font.get(), "hour", color ) )
			{
				success = false;
			}
			
			if( !texture[ 2 ].loadFromRenderedText( renderer, font.get(), "week", color ) )
			{
				success = false;
			}
			
			if( !texture[ 3 ].loadFromRenderedText( renderer, font.get(), "mounth", color ) )
			{
				success = false;
			}
			
			if( !texture[ 4 ].loadFromRenderedText( renderer, font.get(), "year", color ) )
			{
				success = false;
			}
			
			for( int i = 0; i < nr; i ++ )
			{
				texture[ i ].getX() = 0;
			}
		}
	}
	
	return success;
}

void Calendar::render( SDL_Renderer* &renderer, int y )
{
	texture[ 0 ].getY() = y -texture[ 0 ].getH();

	texture[ 1 ].getY() = texture[ 0 ].getY();
	texture[ 2 ].getY() = texture[ 1 ].getB();
	texture[ 3 ].getY() = texture[ 2 ].getB();
	texture[ 4 ].getY() = texture[ 3 ].getB();
	
	for( int i = 0; i < nr; i ++ )
	{
		texture[ i ].render( renderer );
	}
}

void Calendar::handle( SDL_Event &event )
{
	if( SDL_MOUSE)
}
