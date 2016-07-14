#include "bitmapFont.h"
#include <stdio.h>

BitmapFont::BitmapFont()
{
    texture = NULL;
    newLine = 0;
    space = 0;
}

bool BitmapFont::buildFont( Texture* bitmap )
{
    bool success = true;

    //Lock pixels for access
    if( !bitmap->lockTexture() )
    {
        printf( "Unable to lock bitmap font texture!\n" );
        success = false;
    }
    else
    {
        //Set the background color
        Uint32 bgColor = bitmap->getPixel32( 0, 0 );

        //Set the cell dimensions
        int cellW = bitmap->getWidth() / 16;
        int cellH = bitmap->getHeight() / 16;

        //New line variables
        int top = cellH;
        int baseA = cellH;

        //The current character we're setting
        int currentChar = 0;

        //Go through the cell rows
        for( int rows = 0; rows < 16; ++rows )
        {
            //Go through the cell columns
            for( int cols = 0; cols < 16; ++cols )
            {
                //Set the character offset
                chars[ currentChar ].x = cellW * cols;
                chars[ currentChar ].y = cellH * rows;

                //Set the dimensions of the character
                chars[ currentChar ].w = cellW;
                chars[ currentChar ].h = cellH;

                //Find Left Side
                //Go through pixel columns
                for( int col = 0; col < cellW; ++col )
                {
                    //Go through pixel rows
                    for( int row = 0; row < cellH; ++row )
                    {
                        //Get the pixel offsets
                        int pX = ( cellW * cols ) + col;
                        int pY = ( cellH * rows ) + row;

                        //If a non colorkey pixel is found
                        if( bitmap->getPixel32( pX, pY ) != bgColor )
                        {
                            //Set the x offset
                            chars[ currentChar ].x = pX;

                            //Break the loops
                            col = cellW;
                            row = cellH;
                        }
                    }
                }

                //Find Right Side
                //Go through pixel columns
                for( int colW = cellW - 1; colW >= 0; --colW )
                {
                    //Go through pixel rows
                    for( int rowW = 0; rowW < cellH; ++rowW )
                    {
                        //Get the pixel offsets
                        int pX = ( cellW * cols ) + colW;
                        int pY = ( cellH * rows ) + rowW;

                        //If a non colorkey pixel is found
                        if( bitmap->getPixel32( pX, pY ) != bgColor )
                        {
                            //Set the width
                            chars[ currentChar ].w = ( pX - chars[ currentChar ].x ) + 1;

                            //Break the loops
                            colW = -1;
                            rowW = cellH;
                        }
                    }
                }

                //Find Top
                //Go through pixel rows
                for( int row = 0; row < cellH; ++row )
                {
                    //Go through pixel columns
                    for( int col = 0; col < cellW; ++col )
                    {
                        //Get the pixel offsets
                        int pX = ( cellW * cols ) + col;
                        int pY = ( cellH * rows ) + row;

                        //If a non colorkey pixel is found
                        if( bitmap->getPixel32( pX, pY ) != bgColor )
                        {
                            //If new top is found
                            if( row < top )
                            {
                                top = row;
                            }

                            //Break the loops
                            col = cellW;
                            row = cellH;
                        }
                    }
                }

                //Find Bottom of A
                if( currentChar == 'A' )
                {
                    //Go through pixel rows
                    for( int row = cellH - 1; row >= 0; --row )
                    {
                        //Go through pixel columns
                        for( int col = 0; col < cellW; ++col )
                        {
                            //Get the pixel offsets
                            int pX = ( cellW * cols ) + col;
                            int pY = ( cellH * rows ) + row;

                            //If a non colorkey pixel is found
                            if( bitmap->getPixel32( pX, pY ) != bgColor )
                            {
                                //Bottom of a is found
                                baseA = row;

                                //Break the loops
                                col = cellW;
                                row = -1;
                            }
                        }
                    }
                }

                //Go to the next character
                ++currentChar;
            }
        }

        //Calculate space
        space = cellW / 2;

        //Calculate new line
        newLine = baseA - top;

        //Lop off excess top pixels
        for( int i = 0; i < 256; ++i )
        {
            chars[ i ].y += top;
            chars[ i ].h -= top;
        }

        bitmap->unlockTexture();
        texture = bitmap;
    }

    return success;
}

void BitmapFont::renderText( SDL_Renderer* &renderer, int x, int y, std::string text )
{
    //If the font has been built
    if( texture != NULL )
    {
        //Temp offsets
        int curX = x, curY = y;

        //Go through the text
        for( int i = 0; i < text.length(); ++i )
        {
            //If the current character is a space
            if( text[ i ] == ' ' )
            {
                //Move over
                curX += space;
            }
            //If the current character is a newline
            else if( text[ i ] == '\n' )
            {
                //Move down
                curY += newLine;

                //Move back
                curX = x;
            }
            else
            {
                //Get the ASCII value of the character
                int ascii = (unsigned char)text[ i ];

                //Show the character
                texture->render( renderer, curX, curY, &chars[ ascii ] );

                //Move over the width of the character with one pixel of padding
                curX += chars[ ascii ].w + 1;
            }
        }
    }
}
