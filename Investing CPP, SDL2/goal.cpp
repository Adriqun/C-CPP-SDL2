#include "goal.h"
//#include <iostream>

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
    x = 0;
    y = 0;

    renderText = false;
    inputText = "";
    cost = 0;
    focus = false;
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
    focus = false;

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

        if( !goal_text.loadFromRenderedText( renderer, font.get(), "goal:  ", color ) )
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
    if( focus )
    {
        SDL_SetRenderDrawColor( renderer, 0xEC, 0xEC, 0xEC, 0xFF );
        SDL_Rect r = { x, y, 480, static_cast <int> ( goal_text.getHeight() ) };
        SDL_RenderFillRect( renderer, &r );
        SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
    }

    if( renderText )
    {
        cost = strToInt( inputText );
        //std::cout << cost << '\n';

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

    SDL_SetRenderDrawColor( renderer, 0x65, 0x99, 0xFF, 0xFF );
    SDL_RenderDrawLine( renderer, 0, y + goal_text.getHeight() +3, 1000, y + goal_text.getHeight() +3 );
    SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
}

void Goal::handle( SDL_Event &event )
{
    if( event.type == SDL_MOUSEBUTTONDOWN )
    {
        int posX = -1;
        int posY = -1;
        SDL_GetMouseState( &posX, &posY );

        focus = false;

        if( posX > x && posY > y )
        {
            if( posX < x + 480 && posY < y + static_cast <int> ( goal_text.getHeight() ) )
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

                // For better look
                for( unsigned i = 2; i < 11; i += 4 )
                {
                    if( inputText.length() > i )
                    {
                        if( inputText[ i+1 ] != ' ' )
                        {
                            inputText += ' ';
                        }
                    }
                }


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

                // Max number is 999 999 999 999 + 3 space
                if( inputText.length() > 15 )
                {
                    inputText.erase( inputText.length()-1 );
                }
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
