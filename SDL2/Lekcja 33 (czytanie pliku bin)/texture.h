#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL.h>
#include <string>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>

class Texture
{
    SDL_Texture* texture;
    int width;
    int height;

public:
    Texture();
    ~Texture();


    bool loadFromFile( SDL_Renderer *&renderer, std::string path );
    bool loadFromRenderedText( SDL_Renderer *&renderer, std::string textureText, SDL_Color textColor, TTF_Font* font );


    void free();

    void setColor( Uint8 red, Uint8 green, Uint8 blue );
    void setBlendMode( SDL_BlendMode blending );
    void setAlpha( Uint8 alpha );

    void render( SDL_Renderer *&renderer, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

    int getWidth();
    int getHeight();
};



#endif // TEXTURE_H
