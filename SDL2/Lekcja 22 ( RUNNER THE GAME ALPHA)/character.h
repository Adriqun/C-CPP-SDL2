#include <SDL.h>
#include <stdio.h>
#include <string>
#include "universal.h"

#ifndef CHARACTER_H
#define CHARACTER_H
class Character
{
    Universal uni;
    SDL_Texture* character;
    SDL_Rect* spriteCoor;
    SDL_Rect coorChar;

public:
    Character();
    ~Character();
    bool loadMedia(SDL_Renderer* &renderer);
    void present(SDL_Point motion, SDL_Renderer* &renderer);
    void close();
};
#endif
