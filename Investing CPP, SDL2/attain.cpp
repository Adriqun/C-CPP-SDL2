#include "attain.h"

Attain::Attain()
{
    once = "";
    never = "";
}

Attain::~Attain()
{
    free();
}

void Attain::free()
{
    font.free();

    once = "";
    never = "";

    attain.free();
    result.free();
}

bool Attain::load( SDL_Renderer* &renderer, int goal_posY )
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
        color.r = 0x65;
        color.g = 0x99;
        color.b = 0xFF;

        if( !attain.loadFromRenderedText( renderer, font.get(), "attain:  ", color ) )
        {
            success = false;
        }
        else
        {
            attain.getX() = 10;
            attain.getY() = goal_posY;

            never = "never";
            color.r = 0xFF;
            color.g = 0x99;
            color.b = 0x00;

            if( !result.loadFromRenderedText( renderer, font.get(), never, color ) )
            {
                success = false;
            }
            else
            {
                result.getX() = attain.getX() + attain.getW();
                result.getY() = goal_posY;
            }
        }
    }

    return success;
}

void Attain::render( SDL_Renderer* &renderer, int screen_width )
{
    attain.render( renderer );
    result.render( renderer );

    SDL_SetRenderDrawColor( renderer, 0x65, 0x99, 0xFF, 0xFF );

    SDL_RenderDrawLine( renderer, 0, attain.getY() + attain.getH(), screen_width, attain.getY() + attain.getH() );

    SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
}
