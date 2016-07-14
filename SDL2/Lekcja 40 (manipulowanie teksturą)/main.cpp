#include <SDL_image.h>
#include <stdio.h>
#include "texture.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

Texture texture;

bool init()
{
	bool success = true;

	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		window = SDL_CreateWindow( "Lekcja 40", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( window == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( renderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );

				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	bool success = true;

	if( !texture.createBlank( renderer, 15, 16 ) )
    {
        printf( "Nie ustawiono tekstury!\n " );
        success = false;
    }
	else
	{
		//Lock texture
		if( !texture.lockTexture() )
		{
			printf( "Unable to lock Foo' texture!\n" );
		}
		else
		{
			//Get pixel data
			Uint32* pixels = (Uint32*)texture.getPixels();
			int pixelCount = ( texture.getPitch() / 4 ) * texture.getHeight();

			Uint32 colorKey = SDL_MapRGB( SDL_GetWindowSurface( window )->format, 0, 0xFF, 0xFF );
			Uint32 transparent = SDL_MapRGBA( SDL_GetWindowSurface( window )->format, 0xFF, 0xFF, 0xFF, 0xFF );

			for( int i = 0; i < pixelCount; ++i )
			{
				if( pixels[ i ] == colorKey )
				{
					pixels[ i ] = transparent;
				}
			}

			//Unlock texture
			texture.unlockTexture();
		}
	}

	return success;
}

void close()
{
	texture.free();

	SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( window );
	window = NULL;
	renderer = NULL;

	IMG_Quit();
	SDL_Quit();
}

int main( int argc, char* args[] )
{
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
			bool quit = false;
			SDL_Event e;

			while( !quit )
			{
				while( SDL_PollEvent( &e ) != 0 )
				{
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
				}

				SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( renderer );

				//Render stick figure
				texture.render( renderer, ( SCREEN_WIDTH - texture.getWidth() ) / 2, ( SCREEN_HEIGHT - texture.getHeight() ) / 2 );

				SDL_RenderPresent( renderer );
			}
		}
	}

	close();

	return 0;
}
