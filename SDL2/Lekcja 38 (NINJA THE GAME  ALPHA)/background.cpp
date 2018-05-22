#include "background.h"

Background::Background()
{
    width = 1020;
    height = 720;

    rect_one.w = width;
    rect_one.h = height;
    rect_one.x = 0;
    rect_one.y = 0;

    rect_two = rect_one;
    rect_two.x += width;

    texture = NULL;
}

Background::~Background()
{
    SDL_DestroyTexture( texture );
    texture = NULL;
}

void Background::load_texture( SDL_Texture* _texture )
{
    texture = _texture;
}

void Background::draw( SDL_Renderer* &renderer, SDL_Point point )
{
    rect_one.x = point.x;
    rect_one.y = point.y;

    rect_two.x = point.x + 1020;
    rect_two.y = point.y;

    SDL_RenderCopy( renderer, texture, NULL, &rect_one );

    SDL_RenderCopy( renderer, texture, NULL, &rect_two );
}
