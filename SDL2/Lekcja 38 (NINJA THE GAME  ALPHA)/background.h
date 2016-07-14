#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SDL.h>

class Background
{
    uint16_t width, height;
    SDL_Rect rect_one, rect_two;
    SDL_Texture* texture;

public:

    Background();
    ~Background();

    void load_texture( SDL_Texture* _texture );
    void draw( SDL_Renderer* &renderer, SDL_Point point );
};

#endif // BACKGROUND_H

