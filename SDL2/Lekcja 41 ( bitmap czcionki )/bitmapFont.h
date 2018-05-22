#ifndef BITMAPFONT_H
#define BITMAPFONT_H

#include "texture.h"

class BitmapFont
{
    Texture* texture;
    //The individual characters in the surface
    SDL_Rect chars[ 256 ];
    //Spacing Variables
    int newLine, space;

public:

    BitmapFont();
    bool buildFont( Texture *bitmap );
    void renderText( SDL_Renderer* &renderer, int x, int y, std::string text );
};

#endif // BITMAPFONT_H
