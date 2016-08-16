#include "profit.h"
#include <stdio.h>

bool AddCost::load( SDL_Renderer* &renderer, int x, int y )
{
	bool success = true;

    free();
	
    if( !font.load( "data/Chunkfive Ex.ttf", 18 ) )
    {
        success = false;
    }
    else
	{
		color.r = 0xFF;
		color.g = 0xFF;
		color.b = 0xFF;
		if( !label.loadFromRenderedText( renderer, font.get(), "cost: ", color ) )
		{
			success = false;
		}
		else
		{
			label.getX() = x;
			label.getY() = y+3;
		}

		value = "0";
		SDL_Color gray = { 0xFF, 0xFF, 0xFF };
		if( !number.loadFromRenderedText( renderer, font.get(), value, gray ) )
		{
			success = false;
		}
		else
		{
			number.getX() = label.getR();
			number.getY() = y+4;
						
			focusRect.x = label.getX();
			focusRect.y = label.getY()+1;
			focusRect.w = 200;
			focusRect.h = label.getH()-3;
		}
    }

    return success;
}

void AddCost::setY( int y )
{
	label.getY() = y+3;
	number.getY() = y+4;
}

void AddName::handle( SDL_Event &event )
{
    if( event.type == SDL_MOUSEBUTTONDOWN )
    {
        focus = false;

        int x, y;
        SDL_GetMouseState( &x, &y );

        if( y > label.getY() && y < label.getB() )
        {
            if( x < label.getX() + focusRect.w && x > label.getX() )
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

bool AddName::load( SDL_Renderer* &renderer, int x, int y )
{
	bool success = true;

    free();
	
    if( !font.load( "data/Chunkfive Ex.ttf", 18 ) )
    {
        success = false;
    }
    else
    {
		color.r = 0xFF;
		color.g = 0xFF;
		color.b = 0xFF;
		if( !label.loadFromRenderedText( renderer, font.get(), "name: ", color ) )
		{
			success = false;
		}
		else
		{
			label.getX() = x;
			label.getY() = y+3;
		
			value = " ";
			SDL_Color gray = { 0xA4, 0xA4, 0xA4 };
			if( !number.loadFromRenderedText( renderer, font.get(), value, gray ) )
			{
				success = false;
			}
			else
			{
				number.getX() = label.getR();
				number.getY() = y+4;
						
				focusRect.x = label.getX();
				focusRect.y = label.getY()+1;
				focusRect.w = label.getW();
				focusRect.h = label.getH()-3;
			}
		}
    }

    return success;
}

void AddName::render( SDL_Renderer* &renderer )
{
    if( focus )
    {
		focusRect.w = label.getW() + number.getW();
        SDL_SetRenderDrawColor( renderer, 0xB5, 0xB5, 0xB5, 0xFF );
        SDL_RenderFillRect( renderer, &focusRect );
        SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
    }

    if( renderText )
    {
        if( inputText.length() <= 0 )
        {
			SDL_Color gray = { 0xA4, 0xA4, 0xA4 };
            number.loadFromRenderedText( renderer, font.get(), " ", gray );
        }
        else
        {
            number.loadFromRenderedText( renderer, font.get(), inputText, color );
        }

        renderText = false;
    }

    label.render( renderer );
    number.render( renderer );
}

void AddCost::render( SDL_Renderer* &renderer )
{
    if( focus )
    {
		focusRect.w = label.getW() + number.getW();
        SDL_SetRenderDrawColor( renderer, 0xB5, 0xB5, 0xB5, 0xFF );
        SDL_RenderFillRect( renderer, &focusRect );
        SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
    }

    if( renderText )
    {
        if( inputText.length() <= 0 )
        {
			SDL_Color gray = { 0xA4, 0xA4, 0xA4 };
            number.loadFromRenderedText( renderer, font.get(), " ", gray );
        }
        else
        {
            number.loadFromRenderedText( renderer, font.get(), inputText, color );
        }

        renderText = false;
    }

    label.render( renderer );
    number.render( renderer );
}

void AddName::setY( int y )
{
	label.getY() = y+3;
	number.getY() = y+4;
}






Profit::Profit( int ch, int x, int y )
{
	nr = 0;
	texture = NULL;
	
	this->ch = ch;
	
	this->x = x;
	this->y = y;
	
	thrash = false;
	
	addCost = NULL;
}

Profit::~Profit()
{
	free();
}

void Profit::free()
{
	if( addCost != NULL )
	{
		delete addCost;
	}
	
	addName.free();
	
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
	calendar.free();
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
		if( ch == 0 )
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
			texture[ 0 ].getX() = x;
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
	
	addCost = new AddCost;
	addCost->load( renderer, 10, y -2 );
	addName.load( renderer, sw/2 - 50, y -2 );
	
	calendar.load( renderer, sw );
	currency.load( renderer, sw );
	
	return success;
}

void Profit::render( SDL_Renderer* &renderer )
{
	for( int i = 0; i < nr; i++ )
	{
		texture[ i ].render( renderer );
	}
	
	addCost->render( renderer );
	addName.render( renderer );
	
	if( calendar.setFocus() )
	{
		calendar.render( renderer, y );
	}
	
	if( currency.setFocus() )
	{
		currency.render( renderer, y );
	}
}

void Profit::handle( SDL_Event &event )
{
	addName.handle( event );
	addCost->handle( event );
	
	if( event.type == SDL_MOUSEBUTTONDOWN )
	{
		calendar.setFocus() = false;
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
				calendar.setFocus() ? calendar.setFocus() = false: calendar.setFocus() = true;
			}
		}
	}
	
	currency.handle( event );
	calendar.handle( event );
}

bool Profit::isThrash()
{
	return thrash;
}

unsigned long long Profit::getCost()
{
	if( ch == 1 )
		return -addCost->getCost();
	
	return addCost->getCost();
}

int Profit::getCalendar()
{
	return calendar.getPeriod();
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
	
	addCost->setY( y );
	addName.setY( y );
}

