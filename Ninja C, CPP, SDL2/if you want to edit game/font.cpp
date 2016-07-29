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
