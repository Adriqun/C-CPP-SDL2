#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Rect spriteClips[4];
SDL_Texture* spriteTexture;
SDL_Rect dimensions;

bool init()
{
    bool succes=true;
    if(SDL_Init(SDL_INIT_VIDEO)<0)
    {
        printf("Nie zainicjowano SDL'a! SDL Error: %s\n",SDL_GetError());
        succes=false;
    }
    else
    {
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        {
            printf( "Filtrowanie tekstur nie jest wlaczone!\n" );
        }
        window=SDL_CreateWindow("Lekcja 13",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
        if(window==NULL)
        {
            printf("Nie mozna utworzyc okienka! SDL Error: %s\n",SDL_GetError());
            succes=false;
        }
        else
        {
            renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
            if(renderer==NULL)
            {
                printf("Nie mozna utworzyc rendera! SDL Error: %s\n",SDL_GetError());
                succes=false;
            }
            else
            {
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
                int imgFlags=IMG_INIT_PNG;
                if(!(IMG_Init(imgFlags)&imgFlags))
                {
                    printf("Nie mozna zainicjowac IMG INIT! SDL Error %s\n",IMG_GetError());
                    succes=false;
                }
            }
        }
    }
    return succes;
}
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
bool loadMedia()
{
    bool success = true;

    spriteTexture=loadTexture("foo.png");
    if(spriteTexture==NULL)
    {
        printf( "Wczytywanie foo.png nie powiodlo sie!\n" );
        success = false;
    }
    else
    {
        spriteClips[ 0 ].x =   0;
        spriteClips[ 0 ].y =   0;
        spriteClips[ 0 ].w =  64;
        spriteClips[ 0 ].h = 205;

        spriteClips[ 1 ].x =  64;
        spriteClips[ 1 ].y =   0;
        spriteClips[ 1 ].w =  64;
        spriteClips[ 1 ].h = 205;

        spriteClips[ 2 ].x = 128;
        spriteClips[ 2 ].y =   0;
        spriteClips[ 2 ].w =  64;
        spriteClips[ 2 ].h = 205;

        spriteClips[ 3 ].x = 196;
        spriteClips[ 3 ].y =   0;
        spriteClips[ 3 ].w =  64;
        spriteClips[ 3 ].h = 205;
    }
    return success;
}
void close()
{
	SDL_DestroyTexture(spriteTexture);
	SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( window );
	window = NULL;
	renderer = NULL;
    spriteTexture = NULL;

	IMG_Quit();
	SDL_Quit();
}
void update()
{
    bool quit = false;
            SDL_Event e;
            int frame = 0;

            while( !quit )
            {
                while( SDL_PollEvent( &e ) != 0 )
                {
                    if( e.type == SDL_QUIT )
                        quit = true;
                }
                SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
                SDL_RenderClear( renderer );

                SDL_Rect* currentClip = &spriteClips[ frame / 4 ];
                dimensions.x=( SCREEN_WIDTH - currentClip->w ) / 2;
                dimensions.y=( SCREEN_HEIGHT - currentClip->h ) / 2;
                dimensions.w=currentClip->w;
                dimensions.h=currentClip->h;

                SDL_RenderCopy( renderer, spriteTexture, currentClip, &dimensions );

                frame++;
                SDL_Delay(15);
                if( frame/4>=4 )
                    frame=0;

                SDL_RenderPresent( renderer );
            }
}
int main( int argc, char* args[] )
{
    if( !init() )
    {
        printf("Cos poszlo nie tak (init)! \n");
    }
    else
    {
        if( !loadMedia() )
        {
            printf("Cos poszlo nie tak (loadMedia)! \n");
        }
        else
        {
            update();
        }
    }
    close();
    return 0;
}
