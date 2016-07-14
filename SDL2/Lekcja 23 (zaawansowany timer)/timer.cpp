#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include "timer.h"

Timer::Timer()
{
    startTicks=0;
    pausedTicks=0;
    started=false;
    paused=false;
}
void Timer::start()
{
    started=true;
    paused=false;
    startTicks=SDL_GetTicks();
    pausedTicks=0;
}
void Timer::stop()
{
    started=false;
    paused=false;
    startTicks=0;
    pausedTicks=0;
}
void Timer::pause()
{
    //gdy timer jest w tle i nie jest zatrzymany
    if(started && !paused)
    {
        paused=true;

        pausedTicks=SDL_GetTicks()-startTicks;
        startTicks=0;
    }
}
void Timer::unpause()
{
    //gdy timer chodzil i zostal zatrzymany
    if(started && paused)
    {
        paused=false;

        startTicks=SDL_GetTicks()-pausedTicks;
        pausedTicks=0;
    }
}
Uint32 Timer::getTicks()
{
    Uint32 time=0;

    //jesli timer chodzi
    if(started)
    {
        //jesli timer jest zatrzymany
        if(paused)
        {
            //zwroc liczbe sekund kiedy zostal zatrzymany
            time=pausedTicks;
        }
        else
            time=SDL_GetTicks()-startTicks;
    }
    return time;
}
bool Timer::isStarted()
{
    return started;
}
bool Timer::isPaused()
{
    return started&&paused;
}

Texture::Texture()
{
	texture=NULL;
	width=0;
	height=0;
}
Texture::~Texture()
{
	free();
}
bool Texture::loadFromFile( std::string path, SDL_Renderer* &renderer )
{
	free();

	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Nie mozna zaladowac %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			width = loadedSurface->w;
			height = loadedSurface->h;
		}

		SDL_FreeSurface( loadedSurface );
	}

	texture = newTexture;
	return texture != NULL;
}

#ifdef _SDL_TTF_H
bool Texture::loadFromRenderedText( std::string textureText, SDL_Color textColor, TTF_Font* &font, SDL_Renderer* &renderer )
{
	free();

	SDL_Surface* textSurface = TTF_RenderText_Solid( font, textureText.c_str(), textColor );
	if( textSurface != NULL )
	{
        texture = SDL_CreateTextureFromSurface( renderer, textSurface );
		if( texture == NULL )
		{
			printf( "Nie mozna utworzyc tekstury! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{
			width = textSurface->w;
			height = textSurface->h;
		}
		SDL_FreeSurface( textSurface );
	}
	else
		printf( "Nie mozna utworzyc tekstury z powierzchni! SDL_ttf Error: %s\n", TTF_GetError() );

	return texture != NULL;
}
#endif

void Texture::free()
{
	if( texture != NULL )
	{
		SDL_DestroyTexture( texture );
		texture = NULL;
		width = 0;
		height = 0;
	}
}

void Texture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
	SDL_SetTextureColorMod( texture, red, green, blue );
}
void Texture::setBlendMode( SDL_BlendMode blending )
{
	SDL_SetTextureBlendMode( texture, blending );
}
void Texture::setAlpha( Uint8 alpha )
{
	SDL_SetTextureAlphaMod( texture, alpha );
}

void Texture::render( int x, int y, SDL_Renderer* &renderer, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
	SDL_Rect renderQuad = { x, y, width, height };

	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopyEx( renderer, texture, clip, &renderQuad, angle, center, flip );
}

int Texture::getWidth()
{
	return width;
}
int Texture::getHeight()
{
	return height;
}
