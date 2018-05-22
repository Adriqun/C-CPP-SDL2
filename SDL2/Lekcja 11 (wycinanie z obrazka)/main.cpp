#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
SDL_Window* window=NULL;
SDL_Renderer* renderer=NULL;
SDL_Rect spriteClips[4];
SDL_Rect disClips[4];
SDL_Texture* texture;

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
            printf( "Filtrowanie tekstur jest wylaczone!\n" );
        }
        window = SDL_CreateWindow( "Lekcja 11", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( window == NULL )
        {
            printf( "Nie mozna utworzyc okienka! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
            if( renderer == NULL )
            {
                printf( "Render nie moze zostac utworzony! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else
            {
                SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );

                int F = IMG_INIT_PNG;
                if(!(IMG_Init(F)&F))
                {
                    printf( "Nie mozna zainicjowac IMG INIT! SDL_mage Error: %s\n", IMG_GetError() );
                    success = false;
                }
            }
        }
    }
    return success;
}
SDL_Texture* loadTexture(std::string path)
{
    SDL_Texture* newTexture=NULL;
    SDL_Surface* loadedSurface=IMG_Load(path.c_str());

    if(loadedSurface==NULL)
    {
        printf("Nie mozna zaladowac %s ! SDL Error %s\n",path.c_str(),SDL_GetError());
    }
    else
    {
        SDL_SetColorKey(loadedSurface,SDL_TRUE,SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
        newTexture=SDL_CreateTextureFromSurface(renderer,loadedSurface);
        if( newTexture == NULL )
        {
            printf( "Nie mozna utworzyc tekstury z %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}
bool loadMedia()
{
    bool success = true;
    texture=loadTexture("texture.png");
    if(texture==NULL)
    {
        printf( "Nie mozna wczytac texture.png! SDL Error: %s\n",SDL_GetError());
        success = false;
    }
    else
    {
        //Set top left sprite
		spriteClips[ 0 ].x =   0;
		spriteClips[ 0 ].y =   0;
		spriteClips[ 0 ].w = 100;
		spriteClips[ 0 ].h = 100;

		disClips[ 0 ].x =   0;
		disClips[ 0 ].y =   0;
		disClips[ 0 ].w =   100;
		disClips[ 0 ].h =   100;

		//Set top right sprite
		spriteClips[ 1 ].x = 100;
		spriteClips[ 1 ].y =   0;
		spriteClips[ 1 ].w = 100;
		spriteClips[ 1 ].h = 100;

        disClips[ 1 ].x =   SCREEN_WIDTH-spriteClips[1].w;
		disClips[ 1 ].y =   0;
		disClips[ 1 ].w =   100;
		disClips[ 1 ].h =   100;

		//Set bottom left sprite
		spriteClips[ 2 ].x =   0;
		spriteClips[ 2 ].y = 100;
		spriteClips[ 2 ].w = 100;
		spriteClips[ 2 ].h = 100;

		disClips[ 2 ].x =   0;
		disClips[ 2 ].y =   SCREEN_HEIGHT-spriteClips[2].h;
		disClips[ 2 ].w =   100;
		disClips[ 2 ].h =   100;

		//Set bottom right sprite
		spriteClips[ 3 ].x = 100;
		spriteClips[ 3 ].y = 100;
		spriteClips[ 3 ].w = 100;
		spriteClips[ 3 ].h = 100;

		disClips[ 3 ].x =   SCREEN_WIDTH-spriteClips[3].w;
		disClips[ 3 ].y =   SCREEN_HEIGHT-spriteClips[3].h;
		disClips[ 3 ].w =   100;
		disClips[ 3 ].h =   100;
    }
    return success;
}
void close()
{
    SDL_DestroyTexture ( texture );
    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    window = NULL;
    renderer = NULL;
    texture = NULL;

    IMG_Quit();
    SDL_Quit();
}
void update()
{
    bool quit = false;
    SDL_Event e;

    while(!quit)
    {
        while( SDL_PollEvent( &e ) != 0 )
        {
            if( e.type == SDL_QUIT )
                quit = true;
        }
        SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( renderer );

        SDL_RenderCopy(renderer, texture, &spriteClips[0], &disClips[0]);
        SDL_RenderCopy(renderer, texture, &spriteClips[1], &disClips[1]);
        SDL_RenderCopy(renderer, texture, &spriteClips[2], &disClips[2]);
        SDL_RenderCopy(renderer, texture, &spriteClips[3], &disClips[3]);

        SDL_RenderPresent( renderer );
    }
}
int main(int argc, char** args)
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
