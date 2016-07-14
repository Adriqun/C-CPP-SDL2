#include <sstream>
#include "texture.h"

namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int TOTAL_DATA = 10;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

Texture promptTextTexture;
Texture dataTextures[ TOTAL_DATA ];
TTF_Font *font = NULL;

Sint32 data[ TOTAL_DATA ];

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

        window = SDL_CreateWindow( "Lekcja 33", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
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

                if( TTF_Init() == -1 )
                {
                    printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
                    success = false;
                }
            }
        }
    }

    return success;
}

bool loadMedia()
{
    SDL_Color textColor = { 0, 0, 0, 0xFF };
    SDL_Color highlightColor = { 0xFF, 0, 0, 0xFF };

    bool success = true;

    font = TTF_OpenFont( "lazy.ttf", 28 );
    if( font == NULL )
    {
        printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }
    else
    {
        if( !promptTextTexture.loadFromRenderedText( renderer, "Enter Data:", textColor, font ) )
        {
            printf( "Failed to render prompt text!\n" );
            success = false;
        }
    }

    SDL_RWops* file = SDL_RWFromFile( "nums.bin", "r+b" );

    //File does not exist
    if( file == NULL )
    {
        printf( "Warning: Unable to open file! SDL Error: %s\n", SDL_GetError() );

        //Create file for writing
        file = SDL_RWFromFile( "nums.bin", "w+b" );
        if( file != NULL )
        {
            printf( "New file created!\n" );

            //Initialize data
            for( int i = 0; i < TOTAL_DATA; ++i )
            {
                data[ i ] = 0;
                SDL_RWwrite( file, &data[ i ], sizeof(Sint32), 1 );
            }

            //Close file handler
            SDL_RWclose( file );
        }
        else
        {
            printf( "Error: Unable to create file! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
    }
    //File exists
    else
    {
        //Load data
        printf( "Reading file...!\n" );
        for( int i = 0; i < TOTAL_DATA; ++i )
        {
            SDL_RWread( file, &data[ i ], sizeof(Sint32), 1 );
        }

        //Close file handler
        SDL_RWclose( file );
    }

    //Initialize data textures
    dataTextures[ 0 ].loadFromRenderedText( renderer, patch::to_string( (long long)data[ 0 ] ), highlightColor, font );
    for( int i = 1; i < TOTAL_DATA; ++i )
    {
        dataTextures[ i ].loadFromRenderedText( renderer, patch::to_string( (long long )data[ i ] ), textColor, font );
    }

    return success;
}

void close()
{
    //Open data for writing
    SDL_RWops* file = SDL_RWFromFile( "nums.bin", "w+b" );
    if( file != NULL )
    {
        //Save data
        for( int i = 0; i < TOTAL_DATA; ++i )
        {
            SDL_RWwrite( file, &data[ i ], sizeof(Sint32), 1 );
        }

        //Close file handler
        SDL_RWclose( file );
    }
    else
    {
        printf( "Error: Unable to save file! %s\n", SDL_GetError() );
    }

    promptTextTexture.free();
    for( int i = 0; i < TOTAL_DATA; ++i )
        dataTextures[ i ].free();

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

int main( int argc, char* args[] )
{
    if( !init() )
        printf( "Failed to initialize!\n" );
    else
    {
        if( !loadMedia() )
            printf( "Failed to load media!\n" );
        else
        {
            SDL_Event e;

            //Text rendering color
            SDL_Color textColor = { 0, 0, 0, 0xFF };
            SDL_Color highlightColor = { 0xFF, 0, 0, 0xFF };

            //Current input point
            int currentData = 0;

            for( ;; )
            {
                while( SDL_PollEvent( &e ) != 0 )
                {
                    if( e.type == SDL_QUIT )
                        SDL_Quit();

                    else if( e.type == SDL_KEYDOWN )
                    {
                        switch( e.key.keysym.sym )
                        {

                        case SDLK_UP:
                            //Rerender previous entry input point
                            dataTextures[ currentData ].loadFromRenderedText( renderer, patch::to_string( (long long )data[ currentData ] ), textColor, font );
                            --currentData;
                            if( currentData < 0 )
                            {
                                currentData = TOTAL_DATA - 1;
                            }

                            //Rerender current entry input point
                            dataTextures[ currentData ].loadFromRenderedText( renderer, patch::to_string( (long long)data[ currentData ] ), highlightColor, font );
                            break;

                        //Next data entry
                        case SDLK_DOWN:
                            //Rerender previous entry input point
                            dataTextures[ currentData ].loadFromRenderedText( renderer, patch::to_string( (long long)data[ currentData ] ), textColor, font );
                            ++currentData;
                            if( currentData == TOTAL_DATA )
                            {
                                currentData = 0;
                            }

                            //Rerender current entry input point
                            dataTextures[ currentData ].loadFromRenderedText( renderer, patch::to_string( (long long)data[ currentData ] ), highlightColor, font );
                            break;

                        //Decrement input point
                        case SDLK_LEFT:
                            --data[ currentData ];
                            dataTextures[ currentData ].loadFromRenderedText( renderer, patch::to_string( (long long)data[ currentData ] ), highlightColor, font );
                            break;

                        //Increment input point
                        case SDLK_RIGHT:
                            ++data[ currentData ];
                            dataTextures[ currentData ].loadFromRenderedText( renderer, patch::to_string( (long long)data[ currentData ] ), highlightColor, font );
                            break;
                        }
                    }
                }

                SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
                SDL_RenderClear( renderer );

                //Render text textures
                promptTextTexture.render( renderer, ( SCREEN_WIDTH - promptTextTexture.getWidth() ) / 2, 0 );
                for( int i = 0; i < TOTAL_DATA; ++i )
                {
                    dataTextures[ i ].render( renderer, ( SCREEN_WIDTH - dataTextures[ i ].getWidth() ) / 2, promptTextTexture.getHeight() + dataTextures[ 0 ].getHeight() * i );
                }

                SDL_RenderPresent( renderer );
            }
        }
    }

    close();

    return 0;
}
