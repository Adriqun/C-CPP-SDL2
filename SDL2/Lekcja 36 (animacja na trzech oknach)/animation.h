#ifndef ANIMATION_H
#define ANIMATION_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <stdio.h>

class An
{
    Uint8 how_many;
    Uint8 off_set;
    SDL_Texture** texture;

public:
    An();
    ~An();
    std::string int_to_string( int n );
    void setColor( SDL_Texture* &newTexture, Uint8 red, Uint8 green, Uint8 blue );
    void loadTexture( SDL_Renderer* &renderer, SDL_Texture* &newTexture, std::string path );
    void render( SDL_Renderer* &renderer, Uint8 red, Uint8 green, Uint8 blue );
};

#endif // ANIMATION_H
