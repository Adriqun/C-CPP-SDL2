#ifndef CLOCK_H
#define CLOCK_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class Clock
{
    Uint8 nr;
    Uint8 state;

    int width;
    int height;

    SDL_Color color;
    TTF_Font* font;

    SDL_Texture** texture;

public:

    Clock();
    ~Clock();

    void free();
    std::string getTime();

    SDL_Texture* createWithColor( SDL_Renderer* &renderer, int &w, int &h, Uint8 red, Uint8 green, Uint8 blue );
    SDL_Texture* loadFromRenderedText( SDL_Renderer* &renderer, std::string textureText );

    bool load( SDL_Renderer* renderer );
    void render( SDL_Renderer* renderer, SDL_Window* window );

};

#endif // CLOCK_H
