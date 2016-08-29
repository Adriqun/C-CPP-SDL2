#include "profit.h"
#include <stdio.h>

bool Cost::load( SDL_Renderer* &renderer, int x, int y )
{
	bool success = true;

    free();
	
    if( !font.load( "data/Chunkfive Ex.ttf", 18 ) )
    {
        success = false;
    }
    else
	{
		SDL_Color color;
		color.r = 0xFF;
		color.g = 0xFF;
		color.b = 0xFF;
		if( !name.loadFromRenderedText( renderer, font.get(), "cost: ", color ) )
		{
			success = false;
		}
		else
		{
			name.getX() = x;
			name.getY() = y+3;
		}

		SDL_Color gray = { 0xFF, 0xFF, 0xFF };
		if( !line.loadFromRenderedText( renderer, font.get(), line_s, gray ) )
		{
			success = false;
		}
		else
		{
			line.getX() = name.getR();
			line.getY() = y+4;
						
			focusRect.x = name.getX();
			focusRect.y = name.getY()+1;
			focusRect.w = 200;
			focusRect.h = name.getH()-3;
		}
    }

    return success;
}

void Cost::setY( int y )
{
	name.getY() = y+3;
	line.getY() = y+4;
}

void Cost::render( SDL_Renderer* &renderer )
{
    if( focus )
    {
		focusRect.w = name.getW() + line.getW();
        SDL_SetRenderDrawColor( renderer, 0xB5, 0xB5, 0xB5, 0xFF );
        SDL_RenderFillRect( renderer, &focusRect );
        SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
    }

    if( renderText )
    {
        if( inputText.length() <= 0 )
        {
			cost = 0;
			SDL_Color gray = { 0xA4, 0xA4, 0xA4 };
            line.loadFromRenderedText( renderer, font.get(), " ", gray );
        }
        else
        {
			cost = strToInt( inputText );
			SDL_Color color = { 0xFF, 0xFF, 0xFF };
            line.loadFromRenderedText( renderer, font.get(), inputText, color );
        }

        renderText = false;
    }

    name.render( renderer );
    line.render( renderer );
}




bool Name::load( SDL_Renderer* &renderer, int x, int y )
{
	bool success = true;

    free();
	
    if( !font.load( "data/Chunkfive Ex.ttf", 18 ) )
    {
        success = false;
    }
    else
    {
		SDL_Color color;
		color.r = 0xFF;
		color.g = 0xFF;
		color.b = 0xFF;
		if( !name.loadFromRenderedText( renderer, font.get(), "name: ", color ) )
		{
			success = false;
		}
		else
		{
			name.getX() = x;
			name.getY() = y+3;
		
			SDL_Color gray = { 0xA4, 0xA4, 0xA4 };
			if( !line.loadFromRenderedText( renderer, font.get(), line_s, gray ) )
			{
				success = false;
			}
			else
			{
				line.getX() = name.getR();
				line.getY() = y+4;
						
				focusRect.x = name.getX();
				focusRect.y = name.getY()+1;
				focusRect.w = name.getW();
				focusRect.h = name.getH()-3;
			}
		}
    }

    return success;
}

void Name::render( SDL_Renderer* &renderer )
{
    if( focus )
    {
		focusRect.w = name.getW() + line.getW();
        SDL_SetRenderDrawColor( renderer, 0xB5, 0xB5, 0xB5, 0xFF );
        SDL_RenderFillRect( renderer, &focusRect );
        SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
    }

    if( renderText )
    {
        if( inputText.length() <= 0 )
        {
			SDL_Color color = { 0xA4, 0xA4, 0xA4 };
            line.loadFromRenderedText( renderer, font.get(), " ", color );
        }
        else
        {
			SDL_Color color = { 0xFF, 0xFF, 0xFF };
            line.loadFromRenderedText( renderer, font.get(), inputText, color );
        }

        renderText = false;
    }

    name.render( renderer );
    line.render( renderer );
}

void Name::setY( int y )
{
	name.getY() = y+3;
	line.getY() = y+4;
}

void Name::handle( SDL_Event &event )
{
    if( event.type == SDL_MOUSEBUTTONDOWN )
    {
        focus = false;

        int x, y;
        SDL_GetMouseState( &x, &y );

        if( y > name.getY() && y < name.getB() )
        {
            if( x < name.getX() + focusRect.w && x > name.getX() )
            {
                focus = true;
            }
        }
    }

    if( focus )
    {
        if( event.type == SDL_KEYDOWN )
        {
            if( event.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0 )
            {
                inputText.erase( inputText.length()-1 );
                renderText = true;
            }

            else if( event.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL )
            {
                SDL_SetClipboardText( inputText.c_str() );
            }

            else if( event.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL )
            {
                inputText = SDL_GetClipboardText();
                renderText = true;
            }
        }

        else if( event.type == SDL_TEXTINPUT )
        {
            if( !( ( event.text.text[ 0 ] == 'c' || event.text.text[ 0 ] == 'C' ) && ( event.text.text[ 0 ] == 'v' || event.text.text[ 0 ] == 'V' ) && SDL_GetModState() & KMOD_CTRL ) )
            {

                    inputText += event.text.text;
                    renderText = true;

				
                if( focusRect.w > 300 )
                {
                    // printf("%d\n", inputText.length());
                    inputText.erase( inputText.length()-1, 1 );
                }
            }
        }
    }
}






Profit::Profit( int type, int y )
{
	cost = NULL;
	name = NULL;
	
	nr = 0;
	texture = NULL;
	
	this->type = type;
	thrash = false;
	this->y = y;
}

Profit::~Profit()
{
	free();
}

void Profit::free()
{
	if( cost != NULL )
	{
		delete cost;
	}
	
	if( name != NULL )
	{
		delete name;
	}
	
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
	
	thrash = false;
	
	period.free();
	currency.free();
}

	
bool Profit::load( SDL_Renderer* &renderer, SDL_Window* &window )
{
	bool success = true;
	
	free();
	
	int sw, sh;
	SDL_GetWindowSize( window, &sw, &sh );
	
	nr = 4;
	texture = new Texture [ nr ];
	if( texture != NULL )
	{
		SDL_Color color;
		if( type == 0 )
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
		
		// BACKGROUND
		int bar_h = 20;
		if( !texture[ 0 ].createWithColor( renderer, color.r, color.g, color.b, sw, bar_h ) )
		{
			success = false;
		}
		else
		{
			texture[ 0 ].getX() = 0;
			texture[ 0 ].getY() = y;
		}
		
		
		
		if( !texture[ 1 ].loadFromFile( renderer, window, "data/thrash.png" ) )
		{
			success = false;
		}
		else
		{
			texture[ 1 ].getH() = texture[ 1 ].getH()/2.7;
			texture[ 1 ].getW() = texture[ 1 ].getW()/2.5;
			
			texture[ 1 ].getX() = sw - texture[ 1 ].getW()-5;
			texture[ 1 ].getY() = y + bar_h - texture[ 1 ].getH()-1;
		}
		
		if( !texture[ 2 ].loadFromFile( renderer, window, "data/money.png" ) )
		{
			success = false;
		}
		else
		{
			texture[ 2 ].getH() = texture[ 2 ].getH()/2.7;
			texture[ 2 ].getW() = texture[ 2 ].getW()/2.5;
			
			texture[ 2 ].getX() = texture[ 1 ].getX() - 8 - texture[ 2 ].getW();
			texture[ 2 ].getY() = texture[ 1 ].getY() + 2;
		}
		
		if( !texture[ 3 ].loadFromFile( renderer, window, "data/calendar.png" ) )
		{
			success = false;
		}
		else
		{
			texture[ 3 ].getH() = texture[ 3 ].getH()/2.7;
			texture[ 3 ].getW() = texture[ 3 ].getW()/2.5;
			
			texture[ 3 ].getX() = texture[ 2 ].getX() - 8 - texture[ 3 ].getW();
			texture[ 3 ].getY() = texture[ 1 ].getY();
		}
	}
	
	cost = new Cost( 16, true, false, "cost: ", "0" );
	cost->load( renderer, 10, y -2 );
	
	name = new Name( 16, false, false, "name: ", " " );
	name->load( renderer, sw/2 - 50, y -2 );
	
	period.load( renderer, sw );
	currency.load( renderer, sw );
		
	return success;
}

void Profit::render( SDL_Renderer* &renderer )
{
	for( int i = 0; i < nr; i++ )
	{
		texture[ i ].render( renderer );
	}
	
	cost->render( renderer );
	name->render( renderer );
	
	if( period.setFocus() )
	{
		period.render( renderer, y );
	}
	
	if( currency.setFocus() )
	{
		currency.render( renderer, y );
	}
}

void Profit::handle( SDL_Event &event )
{
	name->handle( event );
	cost->handle( event );
	
	if( event.type == SDL_MOUSEBUTTONDOWN )
	{
		period.setFocus() = false;
		currency.setFocus() = false;
		
		int mx, my;
		SDL_GetMouseState( &mx, &my );
		
		if( mx > texture[ 1 ].getX() && mx < texture[ 1 ].getR() )
		{
			if( my > texture[ 1 ].getY() && my < texture[ 1 ].getB() )
			{
				thrash = true;
			}
		}
		
		if( mx > texture[ 2 ].getX() && mx < texture[ 2 ].getR() )
		{
			if( my > texture[ 2 ].getY() && my < texture[ 2 ].getB() )
			{
				currency.setFocus() ? currency.setFocus() = false: currency.setFocus() = true;
			}
		}
		
		if( mx > texture[ 3 ].getX() && mx < texture[ 3 ].getR() )
		{
			if( my > texture[ 3 ].getY() && my < texture[ 3 ].getB() )
			{
				period.setFocus() ? period.setFocus() = false: period.setFocus() = true;
			}
		}
	}
	
	currency.handle( event );
	period.handle( event );
	
	//Temporary color -> set 2016.08.30 -> School is coming :c
	texture[ 2 ].setColor( currency.getColor().r, currency.getColor().g, currency.getColor().b );
	texture[ 3 ].setColor( period.getColor().r, period.getColor().g, period.getColor().b );
}

bool Profit::isThrash()
{
	return thrash;
}

unsigned long long Profit::getCost( int &a )
{
	// printf( "%d\n", cost->getCost() );
	if( type == 1 )
	{
		a = 1;
	}
	else
	{
		a = 0;
	}
	
	return cost->getCost();
}

int Profit::getCalendar()
{
	return period.getPeriod();
}

int Profit::getCurrency()
{
	return currency.getPeriod();
}

int Profit::getH()
{
	return texture[ 0 ].getH();
}

void Profit::setY( int y )
{
	this->y = y;
	texture[ 0 ].getY() = y;
	texture[ 1 ].getY() = y + 20 - texture[ 1 ].getH()-1;
	texture[ 2 ].getY() = texture[ 1 ].getY() + 2;
	texture[ 3 ].getY() = texture[ 1 ].getY();
	
	cost->setY( y );
	name->setY( y );
}

