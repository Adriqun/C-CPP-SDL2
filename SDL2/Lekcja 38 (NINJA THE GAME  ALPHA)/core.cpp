#include "core.h"

namespace core
{
    bool init()
    {
        bool success = true;

        if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
        {
            printf( "Error: %s\n", SDL_GetError() );
            success = false;
        }

        if( !( IMG_Init( IMG_INIT_PNG ) &IMG_INIT_PNG ) )
        {
            printf( "Error: %s\n", IMG_GetError() );
            success = false;
        }

        if( TTF_Init() < 0 )
        {
            printf( "Error: %s\n", TTF_GetError() );
            success = false;
        }

        if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
        {
            printf( "Error: %s\n", Mix_GetError() );
            success = false;
        }

        if( success == false )
        {
            perror( "- nie zainicjowano biblioteki!\n" );
        }

        return success;
    }

    void close_basic( SDL_Renderer* &renderer, SDL_Window* &window )
    {
        SDL_DestroyRenderer( renderer );
        renderer = NULL;

        SDL_DestroyWindow( window );
        window = NULL;

        SDL_Quit();
        IMG_Quit();
        TTF_Quit();
        Mix_Quit();
    }

    void draw_basic( SDL_Renderer* &renderer )
    {
        SDL_RenderPresent( renderer );
        SDL_RenderClear( renderer );
        SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 255 );
    }

    bool create_window( SDL_Window* &window, uint16_t width, uint16_t height )
    {
        window = SDL_CreateWindow( "NINJA GAME", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN );

        if( window == NULL )
        {
            printf( "Nie utworzono okna! Error: %s\n", SDL_GetError() );
            return false;
        }

        return true;
    }

    bool create_renderer( SDL_Renderer* &renderer, SDL_Window* &window )
    {
        renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );

        if( renderer == NULL )
        {
            printf( "Nie utworzono renderera! Error: %s\n", SDL_GetError() );
            return false;
        }
        else
            SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 255 );

        return true;
    }

    SDL_Texture* load_tex( SDL_Renderer* &renderer, std::string path )
    {
        SDL_Surface* surface = IMG_Load( path.c_str() );
        SDL_Texture* newTexture = NULL;

        if( surface == NULL )
        {
            printf( "Nie udalo sie wczytac %s Error %s\n", path.c_str(), IMG_GetError() );
        }
        else
        {
            newTexture = SDL_CreateTextureFromSurface( renderer, surface );
            if( newTexture == NULL )
            {
                printf( "Nie utworzono textury z %s Error %s\n", path.c_str(), SDL_GetError() );
            }
        }

        SDL_FreeSurface( surface );
        return newTexture;
    }

    SDL_Texture* load_tex_re( SDL_Renderer* &renderer, std::string path, SDL_Rect &rect )
    {
        SDL_Surface* surface = IMG_Load( path.c_str() );
        SDL_Texture* newTexture = NULL;

        if( surface == NULL )
        {
            printf( "Nie udalo sie wczytac %s Error %s\n", path.c_str(), IMG_GetError() );
        }
        else
        {
            newTexture = SDL_CreateTextureFromSurface( renderer, surface );
            if( newTexture == NULL )
            {
                printf( "Nie utworzono textury z %s Error %s\n", path.c_str(), SDL_GetError() );
            }
            else
            {
                rect.w = surface -> w;
                rect.h = surface -> h;
            }
        }

        SDL_FreeSurface( surface );
        return newTexture;
    }

    SDL_Texture* load_tex_re_sc( SDL_Renderer* &renderer, std::string path, SDL_Rect &rect, uint8_t w, uint8_t h )
    {
        SDL_Surface* surface = IMG_Load( path.c_str() );
        SDL_Texture* newTexture = NULL;

        if( surface == NULL )
        {
            printf( "Nie udalo sie wczytac %s Error %s\n", path.c_str(), IMG_GetError() );
        }
        else
        {
            newTexture = SDL_CreateTextureFromSurface( renderer, surface );
            if( newTexture == NULL )
            {
                printf( "Nie utworzono textury z %s Error %s\n", path.c_str(), SDL_GetError() );
            }
            else
            {
                rect.w = surface -> w / w;
                rect.h = surface -> h / h;
            }
        }

        SDL_FreeSurface( surface );
        return newTexture;
    }

    Mix_Music* load_music( std::string path )
    {
        Mix_Music* music = Mix_LoadMUS( path.c_str() );
        if( music == NULL )
        {
            printf( "Nie wczytano %s Error %s\n", path.c_str(), Mix_GetError() );
        }

        return music;
    }

    Mix_Chunk* load_chunk( std::string path )
    {
        Mix_Chunk* chunk = Mix_LoadWAV( path.c_str() );
        if( chunk == NULL )
        {
            printf( "Nie wczytano %s Error %s\n", path.c_str(), Mix_GetError() );
        }

        return chunk;
    }

    SDL_Texture* load_fr_re_text( SDL_Renderer* &renderer, std::string path, SDL_Color &color, TTF_Font* &font )
    {
        SDL_Surface* surface = TTF_RenderText_Solid( font, path.c_str(), color );
        SDL_Texture* newTexture = NULL;

        if( surface == NULL )
        {
            printf( "Nie utworzono powierzchni dla tekstu Error %s\n", TTF_GetError() );
        }
        else
        {
            newTexture = SDL_CreateTextureFromSurface( renderer, surface );
            if( newTexture == NULL )
            {
                printf( "Nie utworzono textury z %s Error %s\n", path.c_str(), SDL_GetError() );
            }
        }

        SDL_FreeSurface( surface );
        return newTexture;
    }

    TTF_Font* load_font( std::string path, uint8_t _size )
    {
        TTF_Font* newFont = TTF_OpenFont( path.c_str(), _size );
        if( newFont == NULL )
        {
            printf( "Nie wczytano %s Error %s\n", path.c_str(), TTF_GetError() );
        }

        return newFont;
    }
}
