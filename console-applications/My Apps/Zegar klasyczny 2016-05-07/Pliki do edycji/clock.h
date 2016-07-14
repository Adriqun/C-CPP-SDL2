#ifndef CLOCK_H
#define CLOCK_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class Clock
{
    Uint8 nr;
    SDL_Rect* rect;
    SDL_Texture** texture;

public:

    Clock();
    ~Clock();

    void free();
    std::string getTime();

    int stringToInt( std::string &path );
    SDL_Texture* loadTexture( SDL_Renderer* &renderer, std::string path, SDL_Rect &dstrect );

    bool load( SDL_Renderer* renderer, SDL_Window* window );
    void render( SDL_Renderer* renderer );

};

#endif // CLOCK_H
