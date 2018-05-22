#ifndef NINJA_H
#define NINJA_H

#include <SDL.h>

class Shuriken
{
    uint8_t width, height;
    uint16_t start_x, start_y;
    double angle;

    SDL_Rect rect;
    SDL_Texture* texture;

public:

    Shuriken();
    ~Shuriken();

    void load_texture( SDL_Texture* _texture );
    void draw( SDL_Renderer* &renderer, SDL_Rect _rect, uint8_t value );
};

class Ninja
{
    uint8_t width, height;
    uint16_t start_x, start_y;
    uint8_t nr_offset;

    SDL_Rect rect;
    SDL_Rect* srect;
    SDL_Texture* texture;
    SDL_RendererFlip flip;

public:

    Ninja();
    ~Ninja();

    void load_texture( SDL_Texture* _texture );
    void draw( SDL_Renderer* &renderer, SDL_Rect _rect, uint8_t value );
};

#endif // NINJA_H
