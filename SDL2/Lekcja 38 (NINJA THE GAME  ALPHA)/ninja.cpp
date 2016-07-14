#include "ninja.h"

Shuriken::Shuriken()
{
    width = 28;
    height = 28;

    start_x = -30;
    start_y = 540 + 26;//720 - 128 - 72 + 20

    angle = 0;

    rect.w = width;
    rect.h = height;
    rect.x = start_x;
    rect.y = start_y;

    texture = NULL;
}

Shuriken::~Shuriken()
{
    SDL_DestroyTexture( texture );
    texture = NULL;
}

void Shuriken::load_texture( SDL_Texture* _texture )
{
    texture = _texture;
}

void Shuriken::draw( SDL_Renderer* &renderer, SDL_Rect _rect, uint8_t value )
{
    if( value == 0 )
    {
        rect.x = start_x;
        rect.y = start_y;
    }
    if( value > 0 )
    {
        rect.x = _rect.x;
        rect.y = _rect.y;
    }
    if( value > 1 )
    {
        angle += 20;
        if( angle > 360 )
            angle = 0;
    }

    SDL_RenderCopyEx( renderer, texture, NULL, &rect, angle, NULL, SDL_FLIP_NONE );
}



Ninja::Ninja()
{
    width = 72;
    height = 72;

    start_x = 0;
    start_y = 520 + 26;

    nr_offset = 4;

    rect.w = width;
    rect.h = height;
    rect.x = start_x;
    rect.y = start_y;

    srect = new SDL_Rect[ 8 ];
    for( Uint8 i = 0; i < 8; i++ )
    {
        srect[ i ].x = width * i;
        srect[ i ].y = 0;
        srect[ i ].w = width;
        srect[ i ].h = height;
    }

    texture = NULL;
    flip = SDL_FLIP_NONE;
}

Ninja::~Ninja()
{
    SDL_DestroyTexture( texture );
    texture = NULL;

    delete [] srect;
    srect = NULL;
}

void Ninja::load_texture( SDL_Texture* _texture )
{
    texture = _texture;
}

void Ninja::draw( SDL_Renderer* &renderer, SDL_Rect _rect, uint8_t value )
{
    if( nr_offset > 3 )         nr_offset = 0;          // petla na offset'y

    if( _rect.x > rect.x )          flip = SDL_FLIP_NONE;   // gdzie patrzy postac
    else if( _rect.x < rect.x )     flip = SDL_FLIP_HORIZONTAL;

    if( value != 4 )
    {
        rect.x = _rect.x;
        rect.y = _rect.y;
    }

    if( value == 0 )            nr_offset = 4;  // jesli postac sie nie rusza
    else if( value == 1 )       nr_offset++;    // gdy sie rusza tworzymy animacje
    else if( value == 2 )       nr_offset = 5;  // skok
    else if( value == 3 )       nr_offset = 6;  // atak
    else if( value == 4 )                       // smierc, reset
    {
        rect.x = start_x;
        rect.y = start_y;
        nr_offset = 7;
    }

    SDL_RenderCopyEx( renderer, texture, &srect[ nr_offset ], &rect, 0, NULL, flip );
}
