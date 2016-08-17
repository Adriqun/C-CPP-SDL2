#include "period.h"
#include "font.h"
#include <stdio.h>

Period::Period()
{
	nr = 0;
	texture = NULL;
	
	type = 1;
	
	focus = false;
	
	count = 0;
	whose = 0;
}

Period::~Period()
{
	free();
}

void Period::free()
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
	
	type = 1;
	
	focus = false;
	
	count = 0;
	whose = 0;
}

bool &Period::setFocus()
{
	return focus;
}
	
bool Period::load( SDL_Renderer* &renderer, int screen_width )
{
	register bool success = true;
	
	Font font;
	if( !font.load( "data/Chunkfive Ex.ttf", 15 ) )
	{
		success = false;
	}
	else
	{
		nr = 5;
		texture = new Texture [ nr ];
		
		if( texture != NULL )
		{
			if( !texture[ 0 ].createWithColor( renderer, 0xFF, 0xFF, 0xFF, 80, 65 ) )
			{
				success = false;
			}
			
			SDL_Color color = { 0x58, 0x74, 0x98 };
			
			if( !texture[ 1 ].loadFromRenderedText( renderer, font.get(), "day", color ) )
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
				texture[ i ].getX() = screen_width - texture[ i ].getW() - 3;
			}
		}
	}
	
	return success;
}

void Period::render( SDL_Renderer* &renderer, int y )
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

void Period::handle( SDL_Event &event )
{
	if( focus || count == 1 )
	{
		if( count == 0 )	count = 1;
		
		if( event.type == SDL_MOUSEBUTTONDOWN )
		{
			count = 0;
			int x, y;
			SDL_GetMouseState( &x, &y );
			
			for( int i = 1; i < nr; i ++ )
			{
				if( x > texture[ i ].getX() && x < texture[ i ].getR() )
				{
					if( y > texture[ i ].getY() && y < texture[ i ].getB() )
					{
						type = i;
						whose = i;
						texture[ i ].setColor( 100, 100, 100 );
					}
				}
			}
			
			for( int i = 1; i < nr; i ++ )
			{
				if( i != whose )
					texture[ i ].setColor( 255, 255, 255 );
			}
		}
	}
}

int Period::getPeriod()
{
	return type;
}


bool ProfitCurrency::load( SDL_Renderer* &renderer, int screen_width )
{
	register bool success = true;
	
	Font font;
	if( !font.load( "data/Chunkfive Ex.ttf", 15 ) )
	{
		success = false;
	}
	else
	{
		nr = 5;
		texture = new Texture [ nr ];
		
		if( texture != NULL )
		{
			if( !texture[ 0 ].createWithColor( renderer, 0xFF, 0xFF, 0xFF, 50, 65 ) )
			{
				success = false;
			}
			
			SDL_Color color = { 0x58, 0x74, 0x98 };
			
			if( !texture[ 1 ].loadFromRenderedText( renderer, font.get(), "PLN", color ) )
			{
				success = false;
			}
			
			if( !texture[ 2 ].loadFromRenderedText( renderer, font.get(), "EUR", color ) )
			{
				success = false;
			}
			
			if( !texture[ 3 ].loadFromRenderedText( renderer, font.get(), "USD", color ) )
			{
				success = false;
			}
			
			if( !texture[ 4 ].loadFromRenderedText( renderer, font.get(), "BGP", color ) )
			{
				success = false;
			}
			
			for( int i = 0; i < nr; i ++ )
			{
				texture[ i ].getX() = screen_width - texture[ i ].getW() - 3;
			}
		}
	}
	
	return success;
}
