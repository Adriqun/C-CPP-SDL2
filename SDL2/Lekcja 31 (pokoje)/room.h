#ifndef ROOM_H
#define ROOM_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <stdio.h>

class Room
{
    SDL_Rect rect[ 4 ];

    SDL_Texture* texture[ 4 ];

    Uint8 counter;

public:

    Room();
    ~Room();

    void free();
    SDL_Texture* loadTexture( SDL_Renderer* &renderer, std::string path );
    void load( SDL_Renderer* &renderer );

    void render( SDL_Renderer* &renderer, Uint8 visible );
    SDL_Rect getRect();
};

#endif // ROOM_H
