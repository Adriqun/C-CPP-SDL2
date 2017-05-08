#ifndef INTRO_H
#define INTRO_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <string>

class Intro
{
    Uint8 nr;
    Uint16 counter;

    Mix_Music* music;

    SDL_Color color;
    TTF_Font* font;

    SDL_Rect* rect;
    SDL_Texture** texture;

public:

    Intro();
    ~Intro();

    void free();
    bool isClose();

    SDL_Texture* createWithColor( SDL_Renderer* &renderer, int &w, int &h, Uint8 red, Uint8 green, Uint8 blue );
    SDL_Texture* loadFromRenderedText( SDL_Renderer* &renderer, std::string textureText, int &a, int &b );

    bool load( SDL_Renderer* renderer, SDL_Window* window );
    void render( SDL_Renderer* renderer );

};

#endif // INTRO_H
