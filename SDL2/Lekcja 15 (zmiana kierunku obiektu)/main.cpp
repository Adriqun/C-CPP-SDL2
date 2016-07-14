#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <cmath>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* arrowTexture = NULL;
SDL_Rect clip;
double degrees = 0;
SDL_RendererFlip flipType = SDL_FLIP_NONE;

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

    arrowTexture=loadTexture("arrow.png");
    if(arrowTexture==NULL)
    {
        printf( "Wczytywanie arrow.png nie powiodlo sie!\n" );
        success = false;
    }
    else
    {
        clip.x=( SCREEN_WIDTH - 296 ) / 2;
        clip.y=( SCREEN_HEIGHT - 214 ) / 2;
        clip.w=296;
        clip.h=214;
    }
    return success;
}
void close()
{
    SDL_DestroyTexture(arrowTexture);
    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    window = NULL;
    renderer = NULL;
    arrowTexture = NULL;

    IMG_Quit();
    SDL_Quit();
}
void update()
{
    bool quit = false;
    SDL_Event e;

    while( !quit )
    {
        while( SDL_PollEvent( &e ) != 0 )
        {
            if( e.type == SDL_QUIT )
                quit = true;

            else if( e.type == SDL_KEYDOWN )
            {
                switch( e.key.keysym.sym )
                {
                case SDLK_a:
                    degrees -= 60;
                    break;

                case SDLK_d:
                    degrees += 60;
                    break;

                case SDLK_q:
                    flipType = SDL_FLIP_HORIZONTAL;
                    break;

                case SDLK_w:
                    flipType = SDL_FLIP_NONE;
                    break;

                case SDLK_e:
                    flipType = SDL_FLIP_VERTICAL;
                    break;
                }
            }
        }
        SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( renderer );

        SDL_RenderCopyEx( renderer, arrowTexture, NULL, &clip, degrees, NULL, flipType );

        SDL_RenderPresent( renderer );
    }
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
            update();
        }
    }
    close();
    return 0;
}
