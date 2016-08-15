#include "goal.h"

void Goal::sortString()
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

// Only positive numbers
unsigned long long Goal::strToInt( string s )
{
    unsigned long long tmp = 0;

    for( unsigned i = 0; i < s.size(); i++ )
    {
        if( s[ i ] == ' ' )
            continue;

        tmp = 10 * tmp + s[ i ] - 48;
    }

    return tmp;
}

Goal::Goal()
{
    renderText = false;
    inputText = "";

    cost = 0;
	
    focus = false;
	
	focusRect.x = 0;
	focusRect.y = 0;
	focusRect.w = 0;
	focusRect.h = 0;
	
	value = "";
}

Goal::~Goal()
{
    free();
}

void Goal::free()
{
	font.free();
	
	label.free();
	number.free();

    renderText = false;
    inputText = "";

    cost = 0;

    focus = false;
	
	focusRect.x = 0;
	focusRect.y = 0;
	focusRect.w = 0;
	focusRect.h = 0;
	
	value = "";
}

bool Goal::load( SDL_Renderer* &renderer, int title_bar_height )
{
    bool success = true;

    free();
	
    if( !font.load( "data/Chunkfive Ex.ttf", 30 ) )
    {
        success = false;
    }
    else
    {
		color.r = 0x58;
		color.g = 0x74;
		color.b = 0x98;
		if( !label.loadFromRenderedText( renderer, font.get(), "goal:  ", color ) )
		{
			success = false;
		}
		else
		{
			label.getX() = 10;
			label.getY() = title_bar_height;

			value = "value";
			color.r = 0xA4;
			color.g = 0xA4;
			color.b = 0xA4;
			if( !number.loadFromRenderedText( renderer, font.get(), value, color ) )
			{
				success = false;
			}
			else
			{
				number.getX() = label.getR();
				number.getY() = title_bar_height;
						
				focusRect.x = label.getX();
				focusRect.y = label.getY();
				focusRect.w = 480;
				focusRect.h = label.getH();
						
				color.r = 0x58;
				color.g = 0x70;
				color.b = 0x58;
			}
		}
    }

    return success;
}

void Goal::render( SDL_Renderer* &renderer )
{
    if( focus )
    {
        SDL_SetRenderDrawColor( renderer, 0xEC, 0xEC, 0xEC, 0xFF );
        SDL_RenderFillRect( renderer, &focusRect );
        SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
    }

    if( renderText )
    {
        if( inputText.length() <= 0 )
        {
            cost = 0;
			SDL_Color gray = { 0xA4, 0xA4, 0xA4 };
            number.loadFromRenderedText( renderer, font.get(), value, gray );
        }
        else
        {
            cost = strToInt( inputText );
            number.loadFromRenderedText( renderer, font.get(), inputText, color );
        }

        renderText = false;
    }

    label.render( renderer );
    number.render( renderer );
}

void Goal::renderEdges( SDL_Renderer* &renderer, int screen_width )
{
	SDL_SetRenderDrawColor( renderer, 0x58, 0x74, 0x98, 0xFF );
    SDL_RenderDrawLine( renderer, 0, label.getB() +3, screen_width, label.getB() +3 );
    SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
}

void Goal::handle( SDL_Event &event )
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

                if( inputText[ inputText.length()-1 ] == ' ' )
                {
                    inputText.erase( inputText.length()-1  );
                }

                inputText.erase( inputText.length()-1 );

                sortString();	// delete and add spaces

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

                // We need numbers
                int nr = static_cast <int> ( event.text.text[ 0 ] );
                if( nr >= 48 && nr <= 57 )
                {
                    inputText += event.text.text;
                    renderText = true;
                }

                // We need +number
                if( inputText[ 0 ] == '0' )
                {
                    inputText.erase( 0 );
                }


                // Max number is 999 999 999 999 + 3 spaces
                if( inputText.length() > 16 )
                {
                    // printf("%d\n", inputText.length());
                    inputText.erase( inputText.length()-1, 1 );
                }


                // For better look
                sortString();
            }
        }
    }
}

int Goal::getB()
{
	return label.getB();
}

unsigned long long Goal::getCost()
{
	return cost;
}
