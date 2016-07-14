#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "texture.h"
#include <SDL_mixer.h>

class Control
{
    Uint8 nr;
    Uint8 state;
    Uint8 counter;
    Uint16 *x, *y;

    TTF_Font* font;
    SDL_Color color;

    Texture* texture;
    std::string* caption;

    Uint8 delay;
    Uint8 delay_value;

public:

    Control();
    ~Control();

    void free();
    Uint8 getState();
    void control( SDL_Event &event );

    bool load( SDL_Renderer* renderer, SDL_Window* window );
    void render( SDL_Renderer* renderer );
};

class Ruler
{
    Uint16 x, y;
    Uint8 number;
    unsigned int meters;

    TTF_Font* font;
    SDL_Color color;

    Texture texture;

public:

    Ruler();
    ~Ruler();

    void free();
    std::string intToString( int path );

    bool load( SDL_Renderer* renderer, SDL_Window* window );
    void render( SDL_Renderer* renderer, Uint8 value );
};

class Background
{
    float vel;
    float x, y;

    Texture texture;
    Mix_Music* music;

public:

    Background();
    ~Background();
    void free();

    bool load( SDL_Renderer* renderer, SDL_Window* window );
    void render( SDL_Renderer* renderer, Uint8 value );

};

#endif // BACKGROUND_H
