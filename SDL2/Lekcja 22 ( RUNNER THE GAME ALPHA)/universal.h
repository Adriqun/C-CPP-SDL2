#include <SDL.h>
#include <stdio.h>
#include <string>

#ifndef UNIVERSAL_H
#define UNIVERSAL_H
class Universal
{
public:
    int nr;

    Universal();
    SDL_Texture* loadTexture(std::string path, SDL_Renderer* &renderer);
    int counter (int cage, int fixed);
    SDL_Texture* loadMenuTexture(std::string path, SDL_Renderer* &renderer);
    SDL_Texture* loadRunTexture(std::string path, SDL_Renderer* &renderer);
};
#endif
