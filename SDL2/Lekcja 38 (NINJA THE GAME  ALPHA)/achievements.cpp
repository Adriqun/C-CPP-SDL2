#include "achievements.h"

Skull::Skull()
{
    texture_one = NULL;
    texture_two = NULL;
    rect_one = NULL;
    srect = NULL;
    angle = NULL;

    width = 330;
    height = 413;

    rect_two.w = width / 2;
    rect_two.h = height / 8;
    rect_two.y = 15;
    rect_two.x = 15;

    srect = new SDL_Rect [ 4 ];
    for( Uint8 i = 0; i < 4; i++ )
    {
        srect[ i ].w = 330;
        srect[ i ].h = 413;
        srect[ i ].x = i * 330;
        srect[ i ].y = 0;
    }

    rect_one = new SDL_Rect [ 4 ];
    angle = new double [ 4 ];

    for( Uint8 i = 0; i < 4; i++ )
    {
        rect_one[ i ].w = width / 8;
        rect_one[ i ].h = height / 8;
        rect_one[ i ].y = 15;
        rect_one[ i ].x = 15;
        angle[ i ] = 3;
    }
    rect_one[ 1 ].x += width / 8;
    rect_one[ 2 ].x += width / 4;
    rect_one[ 3 ].x += width / 8 * 3;
}

Skull::~Skull()
{
    texture_one = NULL;
    texture_two = NULL;
    srect = NULL;
    rect_one = NULL;
    angle = NULL;
}

void Skull::load_texture( SDL_Texture* texture, SDL_Texture* _texture )
{
    texture_one = texture;
    texture_two = _texture;
}

void Skull::draw( SDL_Renderer* &renderer, Uint8 value )
{
    SDL_RenderCopy( renderer, texture_two, NULL, &rect_two );

    for( Uint8 i = 0; i < 4; i++ )
    {
        if( value > i )
        {
            SDL_RenderCopyEx( renderer, texture_one, &srect[ i ], &rect_one[ i ], angle[ i ], NULL, SDL_FLIP_NONE );
            if( angle[ i ] > 0 )
                angle[ i ] += 3;

            if( angle[ i ] == 360 )
                angle[ i ] = 0;
        }
    }
}

void Skull::close()
{
    SDL_DestroyTexture( texture_one );
    SDL_DestroyTexture( texture_two );
    delete [] srect;
    delete [] rect_one;
    delete [] angle;
}
