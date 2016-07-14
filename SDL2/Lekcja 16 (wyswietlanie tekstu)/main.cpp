#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
TTF_Font *font = NULL;
SDL_Texture* textTexture;
SDL_Rect rect;

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
                if( TTF_Init() == -1 )
                {
                    printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
                    succes = false;
                }
            }
        }
    }
    return succes;
}
SDL_Texture* loadFromRenderedText( std::string textureText, SDL_Color textColor )
{
    SDL_Surface* textSurface = TTF_RenderText_Solid( font, textureText.c_str(), textColor );

    if( textSurface == NULL )
        printf( "Nie mozna utworzyc powierzchni tekstu! SDL_ttf Error: %s\n", TTF_GetError() );

    else
    {
        textTexture = SDL_CreateTextureFromSurface( renderer, textSurface );
        if( textTexture == NULL )
            printf( "Nie mozna utworzyc tekstury z powierzchni tekstu! SDL Error: %s\n", SDL_GetError() );

        SDL_FreeSurface( textSurface );
    }
    return textTexture;
}
bool loadMedia()
{
    bool success = true;

    font = TTF_OpenFont( "lazy.ttf", 28 );
    if( font == NULL )
    {
        printf( "Nie mozna wczytac lazy.ttf! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }
    else
    {
        SDL_Color textColor = { 0, 0, 0 };
        textTexture=loadFromRenderedText( "The quick brown fox jumps over the lazy dog", textColor );
        if( textTexture==NULL )
        {
            printf( "Blad przy renderowanu tekstu!\n" );
            success = false;
        }

        rect.x=0;
        rect.y=200;
        rect.w=640;
        rect.h=25;
    }
    return success;
}
void close()
{
    SDL_DestroyTexture(textTexture);
    textTexture = NULL;

    TTF_CloseFont( font );
    font = NULL;

    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    window = NULL;
    renderer = NULL;

    TTF_Quit();
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
        }
        SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( renderer );

        SDL_RenderCopyEx( renderer, textTexture, NULL, &rect,0, NULL, SDL_FLIP_NONE );

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
