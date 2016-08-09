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

    texture.free();
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

        if( !texture.loadFromRenderedText( renderer, font.get(), "attain:  ", color ) )
        {
            success = false;
        }
        else
        {
            texture.getX() = 10;
            texture.getY() = goal_posY;

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
                result.getX() = texture.getX() + texture.getW();
                result.getY() = goal_posY;
            }
        }
    }

    return success;
}

void Attain::render( SDL_Renderer* &renderer, int screen_width )
{
    texture.render( renderer );
    result.render( renderer );

    SDL_SetRenderDrawColor( renderer, 0x65, 0x99, 0xFF, 0xFF );

    SDL_RenderDrawLine( renderer, 0, texture.getY() + texture.getH(), screen_width, texture.getY() + texture.getH() );

    SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
}
