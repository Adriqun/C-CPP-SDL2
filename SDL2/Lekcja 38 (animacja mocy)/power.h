#ifndef POWER_H
#define POWER_H

#include <SDL.h>
#include <string>
#include <stdio.h>
#include <SDL_image.h>

class Power
{

protected:

    SDL_Texture* texture;
    SDL_Rect* srcRect;
    SDL_Rect dstRect;
    Uint8 off_sets;
    Uint8 how_many;
    bool counter;
    std::string path;

public:
    Power( int, std::string );
    ~Power();
    void loadTexture( SDL_Renderer *&renderer );
    void load( SDL_Renderer *&renderer );
    void render( SDL_Renderer *&renderer, bool value = false, int x = 0, int y = 0 );
    void close();

};

#endif // POWER_H
