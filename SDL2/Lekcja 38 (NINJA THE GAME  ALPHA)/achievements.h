#ifndef ACHIEVEMENTS_H
#define ACHIEVEMENTS_H

#include <SDL.h>

class Skull
{
    Uint16 width, height;
    SDL_Texture* texture_one;
    SDL_Texture* texture_two;
    SDL_Rect* rect_one;
    SDL_Rect* srect;
    SDL_Rect rect_two;
    double* angle;

public:
    Skull();
    ~Skull();
    void load_texture( SDL_Texture* texture, SDL_Texture* _texture );
    void draw( SDL_Renderer* &renderer, Uint8 value );
    void close();
};

#endif // ACHIEVEMENTS_H
