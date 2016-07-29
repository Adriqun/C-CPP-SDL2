#include "font.h"
#include <stdio.h>

Font::Font()
{
    font = NULL;
}

Font::~Font()
{
    free();
}

void Font::free()
{
    if( font != NULL );
    {
        TTF_CloseFont( font );
        font = NULL;
    }
}


int Font::getOutline()
{
    return TTF_GetFontOutline( font );
}

void Font::setOutline( int outline )
{
    TTF_SetFontOutline( font, outline );
}



void Font::setStyle( unsigned style)
{
    TTF_SetFontStyle( font, style );
}

unsigned Font::getStyle()
{
    return TTF_GetFontStyle( font );
}



int Font::getHinting()
{
    return TTF_GetFontHinting( font );
}

void Font::setHinting( int hinting )
{
    TTF_SetFontHinting( font, hinting );
}



int Font::getKerning()
{
    return TTF_GetFontKerning( font );
}

void Font::setKerning( int allowed )
{
    TTF_SetFontKerning( font, allowed );
}



int Font::getHeight()
{
    return TTF_FontHeight( font );
}

int Font::getAscent()
{
    return TTF_FontAscent( font );
}

int Font::getDescent()
{
    return TTF_FontDescent( font );
}

int Font::getLineSkip()
{
    return TTF_FontLineSkip( font );
}

int Font::getFaces()
{
    return TTF_FontFaces( font );
}



bool Font::faceIsFixedWidth()
{
    return TTF_FontFaceIsFixedWidth( font );
}

char* Font::faceFamilyName()
{
    return TTF_FontFaceFamilyName( font );
}

char* Font::faceStyleName()
{
    return TTF_FontFaceStyleName( font );
}



int Font::glyphIsProvided( Uint16 ch )
{
    return TTF_GlyphIsProvided( font, ch );
}



bool Font::load( const char* path, int size )
{
    bool success = true;

    free();

    font = TTF_OpenFont( path, size );
    if( font == NULL )
    {
        printf( "Not found font %s\n", path );
        printf( "Error %s\n", TTF_GetError() );
        success = false;
    }

    return success;
}

TTF_Font* Font::get()
{
    return font;
}
