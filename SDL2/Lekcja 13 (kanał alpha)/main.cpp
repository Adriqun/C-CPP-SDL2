#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

const int SCREEN_WIDTH=640;
const int SCREEN_HEIGHT=480;
SDL_Window* window=NULL;
SDL_Renderer* renderer=NULL;
SDL_Texture* modulated=NULL;
SDL_Texture* background=NULL;

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

    modulated=loadTexture("fadeout.png");
    if(modulated==NULL)
    {
        printf( "Wczytywanie fadeout.png nie powiodlo sie!\n" );
        success = false;
    }
    else
        SDL_SetTextureBlendMode( modulated, SDL_BLENDMODE_BLEND );

    background=loadTexture("fadein.png");
    if(background==NULL)
    {
        printf( "Wczytywanie fadein.png nie powiodlo sie!\n" );
        success = false;
    }

    return success;
}
void close()
{
    SDL_DestroyTexture( modulated );
    SDL_DestroyTexture( background );
    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    window = NULL;
    renderer = NULL;
    modulated = NULL;
    background = NULL;

    IMG_Quit();
    SDL_Quit();
}
void update()
{
    SDL_Event e;
    bool quit=false;
    Uint8 a = 255;

    while(!quit)
    {
        while(SDL_PollEvent(&e)!=0)
        {
            if(e.type==SDL_QUIT)
                quit=true;
            else if(e.type==SDL_KEYDOWN)
            {
                if( e.key.keysym.sym == SDLK_w )
                {
                    if(a+32>255)
                        a=255;

                    else
                        a += 32;
                }
                else if( e.key.keysym.sym == SDLK_s )
                {
                    if(a-32<0)
                        a=0;

                    else
                        a -= 32;
                }
            }
        }
        SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( renderer );

        SDL_RenderCopy( renderer, background, NULL, NULL);
        SDL_SetTextureAlphaMod(modulated, a);
        SDL_RenderCopy( renderer, modulated, NULL, NULL);

        SDL_RenderPresent( renderer );
    }
}
int main(int argc, char *argv[])
{
    if(!init())
    {
        printf("Cos poszlo nie tak (init)! \n");
    }
    else
    {
        if(!loadMedia())
        {
            printf("Cos poszlo nie tak (loadMedia)! \n");
        }
        else
        {
            update();
        }
    }
    close();
    return  0;
}
