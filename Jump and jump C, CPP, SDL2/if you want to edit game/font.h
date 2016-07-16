#pragma once

#include <SDL_ttf.h>

class Font
{
    TTF_Font* font;

public:

    Font();
    ~Font();

    void free();
    bool load( const char* path, int size );

    TTF_Font* get();
};
