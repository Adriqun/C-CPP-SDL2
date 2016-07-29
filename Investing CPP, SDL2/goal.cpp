#include "goal.h"

// Only +numbers
int Goal::strToInt( string s )
{
    int tmp = 0;

    for( unsigned i = 0; i < s.size(); i++ )
    {
        tmp = 10 * tmp + s[ i ] - 48;
    }

    return tmp;
}

Goal::Goal()
{
    x = 0;
    y = 0;

    renderText = false;
    inputText = "";
    cost = 0;
}

Goal::~Goal()
{
    free();
}

void Goal::free()
{
    x = 0;
    y = 0;

    renderText = false;
    inputText = "";
    cost = 0;

    texture.free();
    goal_text.free();
    font.free();
}

bool Goal::load( SDL_Renderer* &renderer )
{
    bool success = true;

    free();

    if( !font.load( "data/Chunkfive Ex.ttf", 30 ) )
    {
        success = false;
    }
    else
    {
        color.r = 0x65;
        color.g = 0x99;
        color.b = 0xFF;

        font.setStyle( 2 );

        if( !goal_text.loadFromRenderedText( renderer, font.get(), "Goal  ", color ) )
        {
            success = false;
        }
        else
        {
            x = 10;
            y = 60;

            color.r = 0x09;
            color.g = 0x70;
            color.b = 0x54;

            font.setStyle( 0 );

            if( !texture.loadFromRenderedText( renderer, font.get(), "0", color ) )
            {
                success = false;
            }
        }
    }

    return success;
}

void Goal::render( SDL_Renderer* &renderer )
{
    if( renderText )
    {
        cost = strToInt( inputText );

        if( inputText.length() <= 0 )
        {
            texture.loadFromRenderedText( renderer, font.get(), "0", color );
        }
        else
            texture.loadFromRenderedText( renderer, font.get(), inputText, color );

        renderText = false;
    }

    goal_text.render( renderer, x, y );
    texture.render( renderer, x + goal_text.getWidth(), y );
}

void Goal::handle( SDL_Event &event )
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

            // Max number is 999 999 999
            if( inputText.length() > 9 )
            {
                inputText.erase( inputText.length()-1 );
            }
        }
    }
}

unsigned Goal::getWidth()
{
    return texture.getWidth();
}

unsigned Goal::getHeight()
{
    return texture.getHeight();
}
