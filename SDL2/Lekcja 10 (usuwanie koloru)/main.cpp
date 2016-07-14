#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

const int SCREEN_WIDTH=640;
const int SCREEN_HEIGHT=480;
SDL_Window* window=NULL;
SDL_Renderer* renderer=NULL;
SDL_Texture* sheep=NULL;
SDL_Texture* background=NULL;

SDL_Texture* loadTexture(std::string path)
{
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
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
            printf( "Nie mozna stworzyc tekstury z %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }
        SDL_FreeSurface( loadedSurface );
    }
    return newTexture;
}
bool init()
{
	bool success = true;
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "Nie mozna zainicjowac SDL'a! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Filtrowanie tekstur nie zostalo wlaczone!\n" );
		}
		window = SDL_CreateWindow( "Lekcja 10", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( window == NULL )
		{
			printf( "Nie utworzono okienka! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
			if( renderer == NULL )
			{
				printf( "Render nie zostal stworzony! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "Nie zainicjowano IMG INIT! SDL_image Error: %s\n", IMG_GetError() );
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
	sheep=loadTexture("statek.png");
	if(sheep==NULL)
	{
		printf( "Blad przy ladowaniu statek.png !\n" );
		success = false;
	}

	background=loadTexture("tlo.png");
	if(sheep==NULL)
	{
		printf( "Blad przy ladowaniu tlo.png !\n" );
		success = false;
	}

	return success;
}
void close()
{
	SDL_DestroyTexture( sheep );
	SDL_DestroyTexture( background );
	SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( window );
	window = NULL;
	renderer = NULL;
    sheep=NULL;
    background=NULL;
	IMG_Quit();
	SDL_Quit();
}
void update()
{
    SDL_Event e;
    bool quit=false;

    while(!quit)
    {
        while(SDL_PollEvent(&e)!=0)
        {
            if(e.type==SDL_QUIT)
                quit=true;
        }
        SDL_SetRenderDrawColor(renderer,0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, background, NULL, NULL);
        SDL_RenderCopy(renderer, sheep, NULL, NULL);

        SDL_RenderPresent(renderer);
    }
}
int main(int argc,char**args)
{
    if(!init())
    {
        printf("Cos poszlo nie tak (init)!\n");
    }
    else
    {
        if(!loadMedia())
        {
            printf("Cos poszlo nie tak (loadMedia)!\n");
        }
        else
        {
            update();
        }
    }
    close();
    return 0;
}
