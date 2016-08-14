#include "profit.h"

void Profit::sortString()
{
    for( unsigned i = 0; i < inputText.length(); i ++ )
    {
        if( inputText[ i ] == ' ' )
        {
            inputText.erase( i, 1 );
        }
    }

    string newInputText = "";
    int c = inputText.length()-1;
    for( unsigned i = 0; i < inputText.length(); i ++ )
    {
        newInputText += inputText[ i ];

        if( c%3 == 0 )
        {
            newInputText += ' ';
        }

        c --;
    }
    inputText = newInputText;
}

// Only +numbers
long long Profit::strToInt( string s )
{
    long long tmp = 0;

    for( unsigned i = 0; i < s.size(); i++ )
    {
        if( s[ i ] == ' ' )
            continue;

        tmp = 10 * tmp + s[ i ] - 48;
    }

    return tmp;
}

Profit::Profit( char c, int x, int y )
{
	texture = NULL;
	name = "";
	renderText = false;
	cost = 0;
	inputText = "";
	
	focus = false;
	focus_w = 0;
	
	this->c = c;
	nr = 0;
	
	this->x = x;
	this->y = y;
}

Profit::~Profit()
{
	free();
}

void Profit::free()
{
	font.free();
	
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
	
	name = "";
	renderText = false;
	cost = 0;
	inputText = "";
	
	focus = false;
	focus_w = 0;
	
	c = 'c';
	nr = 0;
}

	
bool Profit::load( SDL_Renderer* &renderer, SDL_Window* &window )
{
	register bool success = true;
	
	free();
	
	if( !font.load( "data/Chunkfive Ex.ttf", 20 ) )
	{
		success = false;
	}
	
	nr = 7;
	texture = new Texture [ nr ];
	if( texture != NULL && success )
	{
		int sw, sh;
		SDL_GetWindowSize( window, &sw, &sh );
		
		if( c == 'c' )
		{
			color.r = 0xE8;
			color.g = 0x68;
			color.b = 0x50;
		}
		else
		{
			color.r = 0x58;
			color.g = 0x70;
			color.b = 0x58;
		}
		
		int bar_width = 20;
		if( !texture[ 0 ].createWithColor( renderer, color.r, color.g, color.b, sw, bar_width ) )
		{
			success = false;
		}
		
		color.r = 0xE8;
		color.g = 0x68;
		color.b = 0x50;
		if( !texture[ 1 ].loadFromRenderedText( renderer, font.get(), "delete", color ) )
		{
			success = false;
		}
		else
		{
			texture[ 1 ].setAlpha( 100 );
			texture[ 1 ].getX() = sw - texture[ 1 ].getW();
			texture[ 1 ].getY() = y + bar_width - texture[ 1 ].getH();
		}
		
		
		color.r = 0xA4;
		color.g = 0xA4;
		color.b = 0xA4;
		if( !texture[ 2 ].loadFromRenderedText( renderer, font.get(), "value: ", color ) )
		{
			success = false;
		}
		else
		{
			texture[ 2 ].getX() = x + 5;
			texture[ 2 ].getY() = y + 5;
		}
		
		
	}
	
	return success;
}

void Profit::render( SDL_Renderer* &renderer )
{
	for( int i = 0; i < nr; i++ )
	{
		texture[ i ].render( renderer );
	}
}
