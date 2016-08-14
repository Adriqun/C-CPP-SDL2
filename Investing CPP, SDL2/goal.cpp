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

// Only +numbers
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
    focus_w = 0;
	
	font = NULL;
	goal = NULL;
	number = NULL;
}

Goal::~Goal()
{
    free();
}

void Goal::free()
{
	if( font != NULL )
	{
		delete font;
	}

    renderText = false;
    inputText = "";

    cost = 0;

    focus = false;
    focus_w = 0;
	
	if( goal != NULL )
	{
		delete goal;
	}
	
	if( number != NULL )
	{
		delete number;
	}
}

bool Goal::load( SDL_Renderer* &renderer, int title_bar_posY )
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
        color.r = 0x58;
        color.g = 0x74;
        color.b = 0x98;
		
		goal = new Texture;
		if( goal == NULL )	success = NULL;
        else if( !goal->loadFromRenderedText( renderer, font->get(), "goal:  ", color ) )
        {
            success = false;
        }
        else
        {
            goal->getX() = 10;
            goal->getY() = title_bar_posY;

            color.r = 0x58;
            color.g = 0x70;
            color.b = 0x58;
			
			SDL_Color gray = { 0xA4, 0xA4, 0xA4 };
			number = new Texture;
			if( number == NULL )	success = NULL;
            if( !number->loadFromRenderedText( renderer, font->get(), "value", gray ) )
            {
                success = false;
            }
            else
            {
                number->getX() = goal->getX() + goal->getW();
                number->getY() = title_bar_posY;
                focus_w = 480;
            }
        }
    }

    return success;
}

void Goal::render( SDL_Renderer* &renderer, int screen_width )
{
    if( focus )
    {
        SDL_SetRenderDrawColor( renderer, 0xEC, 0xEC, 0xEC, 0xFF );

        SDL_Rect r = { goal->getX(), goal->getY(), focus_w, goal->getH() };

        SDL_RenderFillRect( renderer, &r );

        SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
    }

    if( renderText )
    {
        if( inputText.length() <= 0 )
        {
            cost = 0;
			SDL_Color gray = { 0xA4, 0xA4, 0xA4 };
            number->loadFromRenderedText( renderer, font->get(), "value", gray );
        }
        else
        {
            cost = strToInt( inputText );
            number->loadFromRenderedText( renderer, font->get(), inputText, color );
        }

        renderText = false;
    }

    goal->render( renderer );
    number->render( renderer );



    SDL_SetRenderDrawColor( renderer, 0x58, 0x74, 0x98, 0xFF );

    SDL_RenderDrawLine( renderer, 0, goal->getY() + goal->getH() +3, screen_width, goal->getY() + goal->getH() +3 );

    SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
}

void Goal::handle( SDL_Event &event )
{
    if( event.type == SDL_MOUSEBUTTONDOWN )
    {
        focus = false;

        int x, y;
        SDL_GetMouseState( &x, &y );

        if( x > goal->getX() && y > goal->getY() )
        {
            if( x < goal->getX() + focus_w && y < goal->getY() + goal->getH() )
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

                sortString();

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

int Goal::getW()
{
    return goal->getW() + number->getW();
}

int &Goal::getH()
{
    return goal->getH();
}

int &Goal::getX()
{
    return goal->getX();
}

int &Goal::getY()
{
    return goal->getY();
}

unsigned long long Goal::getCost()
{
	return cost;
}
