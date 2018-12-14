#pragma once

#include <SDL2/SDL_ttf.h>

class Font
{
    TTF_Font* font;

public:

    Font();
    ~Font();
    void free();

    int getOutline();
    void setOutline( int outline = 0 );

    // 0, 1, 2, 4, 8
    unsigned getStyle();
    void setStyle( unsigned style = TTF_STYLE_NORMAL );

    // 0, 1, 2, 3
    int getHinting();
    void setHinting( int hinting = TTF_HINTING_NORMAL );

    int getKerning();
    void setKerning( int allowed = 0 );

    int getHeight();
    int getAscent();
    int getDescent();
    int getLineSkip();
    int getFaces();

    bool faceIsFixedWidth();
    char* faceFamilyName();
    char* faceStyleName();

    int glyphIsProvided( Uint16 ch );

    bool load( const char* path, int size );

    TTF_Font* get();
};
