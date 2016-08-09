#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

using namespace std;

class Texture
{
    SDL_Rect rect;
    SDL_Texture* texture;

public:
	
    Texture( int x = 0, int y = 0 );
    ~Texture();
    void free();

    int &getX();
    int &getY();
    int &getW();
    int &getH();

    void setAlpha( Uint8 alpha );
    void setColor( Uint8 red, Uint8 green, Uint8 blue );
    void setBlendMode( SDL_BlendMode blendMode );

    bool createWithColor( SDL_Renderer* &renderer, Uint8 r, Uint8 g, Uint8 b, unsigned w, unsigned h );
    bool loadFromRenderedText( SDL_Renderer* &renderer, TTF_Font* font, string text, SDL_Color color );
    bool loadFromFile( SDL_Renderer* &renderer, SDL_Window* &window, string path );

    void render( SDL_Renderer* &renderer, SDL_Rect* srcRect = NULL, double angle = 0.0, SDL_Point* point = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );
};
