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



Goal::Goal( int letters, bool space, bool renderEdges, string name_s, string line_s, int bot_scope, int top_scope )
{
	this->name_s = name_s;
	this->line_s = line_s;
	
    renderText = false;
    inputText = "";

    cost = 0;
	
    focus = false;
	focusRect.x = 0;
	focusRect.y = 0;
	focusRect.w = 0;
	focusRect.h = 0;
	
	this->bot_scope = bot_scope;
	this->top_scope = top_scope;
	
	this->renderEdges = renderEdges;
	this->space = space;
	this->letters = letters;
}

Goal::~Goal()
{
    free();
}

void Goal::free()
{
	font.free();
	
	name.free();
	line.free();

    renderText = false;
    inputText = "";

    cost = 0;

    focus = false;
	focusRect.x = 0;
	focusRect.y = 0;
	focusRect.w = 0;
	focusRect.h = 0;
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
		SDL_Color color;
		
		color.r = 0x58;
		color.g = 0x74;
		color.b = 0x98;
		if( !name.loadFromRenderedText( renderer, font.get(), name_s, color ) )
		{
			success = false;
		}
		else
		{
			name.getX() = 10;
			name.getY() = title_bar_height;
		}
		
		
		color.r = 0xA4;
		color.g = 0xA4;
		color.b = 0xA4;
		if( !line.loadFromRenderedText( renderer, font.get(), line_s, color ) )
		{
			success = false;
		}
		else
		{
			line.getX() = name.getR();
			line.getY() = title_bar_height;
		}
		
		
		focusRect.x = 3;
		focusRect.y = title_bar_height-5;
		focusRect.w = 500;
		focusRect.h = name.getH()+9;
    }

    return success;
}

void Goal::render( SDL_Renderer* &renderer, int screen_width )
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
			SDL_Color color = { 0xA4, 0xA4, 0xA4 };
            line.loadFromRenderedText( renderer, font.get(), line_s, color );
        }
        else
        {
            cost = strToInt( inputText );
			SDL_Color color = { 0x58, 0x70, 0x58 };
            line.loadFromRenderedText( renderer, font.get(), inputText, color );
        }

        renderText = false;
    }

    name.render( renderer );
    line.render( renderer );
	
	if( renderEdges )
	{
		SDL_SetRenderDrawColor( renderer, 0x58, 0x74, 0x98, 0xFF );
		SDL_RenderDrawLine( renderer, 0, name.getB() +3, screen_width, name.getB() +3 );
		SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
	}
	
	//printf( "%d, %d\n", name.getX(), name.getY() );
}

void Goal::handle( SDL_Event &event )
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
				
				if( space )
				{
					if( inputText[ inputText.length()-1 ] == ' ' )
					{
						inputText.erase( inputText.length()-1  );
					}

					inputText.erase( inputText.length()-1 );
					sortString();	// delete and add spaces
				}

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
                if( nr >= bot_scope && nr <= top_scope )
                {
                    inputText += event.text.text;
                    renderText = true;
                }
				
				if( space )
				{
					// We need +number
					if( inputText[ 0 ] == '0' )
					{
						inputText.erase( 0 );
					}
				}
                

                // Max number is 999 999 999 999 + 3 spaces
                if( inputText.length() > letters )
                {
                    // printf("%d\n", inputText.length());
                    inputText.erase( inputText.length()-1, 1 );
                }

				if( space )
				{
					// For better look
					sortString();
				}
            }
        }
    }
}

int Goal::getB()
{
	return name.getB();
}

unsigned long long Goal::getCost()
{
	return cost;
}
