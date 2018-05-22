#include <SDL_image.h>
#include <stdio.h>
#include "texture.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

Texture targetTexture;

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

		window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
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

				if( !( IMG_Init( IMG_INIT_PNG ) & IMG_INIT_PNG ) )
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

	if( !targetTexture.createBlank( renderer, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_TEXTUREACCESS_TARGET ) )
	{
		printf( "Failed to create target texture!\n" );
		success = false;
	}

	return success;
}

void close()
{
	targetTexture.free();

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

			double angle = 0;
			SDL_Point screenCenter = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };

			while( quit == false )
			{
				while( SDL_PollEvent( &e ) != 0 )
				{
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
				}

				angle += 2;
				if( angle > 360 )
				{
					angle -= 360;
				}

				targetTexture.setAsRenderTarget( renderer );

				SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( renderer );

				//Render red filled quad
				SDL_Rect fillRect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
				SDL_SetRenderDrawColor( renderer, 0xFF, 0x00, 0x00, 0xFF );
				SDL_RenderFillRect( renderer, &fillRect );

				//Render green outlined quad
				SDL_Rect outlineRect = { SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6, SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT * 2 / 3 };
				SDL_SetRenderDrawColor( renderer, 0x00, 0xFF, 0x00, 0xFF );
				SDL_RenderDrawRect( renderer, &outlineRect );

				//Draw blue horizontal line
				SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0xFF, 0xFF );
				SDL_RenderDrawLine( renderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2 );

				//Draw vertical line of yellow dots
				SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0x00, 0xFF );
				for( int i = 0; i < SCREEN_HEIGHT; i += 4 )
				{
					SDL_RenderDrawPoint( renderer, SCREEN_WIDTH / 2, i );
				}

				//Reset render target
				SDL_SetRenderTarget( renderer, NULL );

				//Show rendered to texture
				targetTexture.render( renderer, 0, 0, NULL, angle, &screenCenter );

				SDL_RenderPresent( renderer );
			}
		}
	}

	close();

	return 0;
}
