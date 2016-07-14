#include "animation.h"
#include "window.h"

const int TOTAL_WINDOWS = 3;
Window windows[ TOTAL_WINDOWS ];
An texture_one;
An texture_two;

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		if( !windows[ 0 ].init() )
		{
			printf( "Window 0 could not be created!\n" );
			success = false;
		}
		if( !( IMG_Init( IMG_INIT_PNG ) &IMG_INIT_PNG ) )
        {
            printf( "Nie zainicjowano PNG!\n" );
			success = false;
        }
	}

	return success;
}

void close()
{
	for( int i = 0; i < TOTAL_WINDOWS; ++i )        windows[ i ].free();

	SDL_Quit();
}

int main( int argc, char* args[] )
{
	if( !init() )
		printf( "Failed to initialize!\n" );

	else
	{
		for( int i = 1; i < TOTAL_WINDOWS; ++i )    windows[ i ].init();

		bool quit = false;
		SDL_Event e;

		while( !quit )
		{
			while( SDL_PollEvent( &e ) != 0 )
			{
				if( e.type == SDL_QUIT )
					quit = true;


				for( int i = 0; i < TOTAL_WINDOWS; ++i )    windows[ i ].handleEvent( e );


				if( e.type == SDL_KEYDOWN )
				{
					switch( e.key.keysym.sym )
					{
						case SDLK_1:
						windows[ 0 ].focus();
						break;

						case SDLK_2:
						windows[ 1 ].focus();
						break;

						case SDLK_3:
						windows[ 2 ].focus();
						break;
					}
				}
			}


            texture_one.render( windows[ 0 ].renderer, 25, 125, 80 );
            texture_one.render( windows[ 1 ].renderer, 0, 20, 250 );
            texture_one.render( windows[ 2 ].renderer, 0, 250, 0 );
			for( int i = 0; i < TOTAL_WINDOWS; ++i )
            {
                windows[ i ].render();
            }



			bool alWindowsClosed = true;
			for( int i = 0; i < TOTAL_WINDOWS; ++i )
			{
				if( windows[ i ].isShown() )
				{
					alWindowsClosed = false;
					break;
				}
			}

			if( alWindowsClosed )
				quit = true;
		}
	}

	close();

	return 0;
}
