#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <sstream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


class Texture
{
    SDL_Texture* texture;
    int width;
    int height;

public:
    Texture();
    ~Texture();

    bool loadFromFile( std::string path );
    void free();

    void setColor( Uint8 red, Uint8 green, Uint8 blue );
    void setBlendMode( SDL_BlendMode blending );
    void setAlpha( Uint8 alpha );

    void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

    int getWidth();
    int getHeight();
};

class Window
{
    SDL_Window* window;

    int width;
    int height;

    bool mouseFocus;
    bool keyboardFocus;
    bool fullScreen;
    bool minimized;

public:
    Window();
    bool init();
    SDL_Renderer* createRenderer();
    void handleEvent( SDL_Event& e );
    void free();

    int getWidth();
    int getHeight();

    bool hasMouseFocus();
    bool hasKeyboardFocus();
    bool isMinimized();
};

bool init();
bool loadMedia();
void close();

Window window;

SDL_Renderer* renderer = NULL;

Texture sceneTexture;


Texture::Texture()
{
    texture = NULL;
    width = 0;
    height = 0;
}

Texture::~Texture()
{
    free();
}

bool Texture::loadFromFile( std::string path )
{
    free();

    SDL_Texture* newTexture = NULL;

    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }
        else
        {
            width = loadedSurface->w;
            height = loadedSurface->h;
        }

        SDL_FreeSurface( loadedSurface );
    }

    texture = newTexture;
    return texture != NULL;
}

void Texture::free()
{
    if( texture != NULL )
    {
        SDL_DestroyTexture( texture );
        texture = NULL;
        width = 0;
        height = 0;
    }
}

void Texture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
    SDL_SetTextureColorMod( texture, red, green, blue );
}

void Texture::setBlendMode( SDL_BlendMode blending )
{
    SDL_SetTextureBlendMode( texture, blending );
}

void Texture::setAlpha( Uint8 alpha )
{
    SDL_SetTextureAlphaMod( texture, alpha );
}

void Texture::render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
    SDL_Rect renderQuad = { x, y, width, height };

    if( clip != NULL )
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    SDL_RenderCopyEx( renderer, texture, clip, &renderQuad, angle, center, flip );
}

int Texture::getWidth()
{
    return width;
}

int Texture::getHeight()
{
    return height;
}

Window::Window()
{
    //Initialize non-existant window
    window = NULL;
    mouseFocus = false;
    keyboardFocus = false;
    fullScreen = false;
    minimized = false;
    width = 0;
    height = 0;
}

bool Window::init()
{
    //Create window
    window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE );
    if( window != NULL )
    {
        mouseFocus = true;
        keyboardFocus = true;
        width = SCREEN_WIDTH;
        height = SCREEN_HEIGHT;
    }

    return window != NULL;
}

SDL_Renderer* Window::createRenderer()
{
    return SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
}

void Window::handleEvent( SDL_Event& e )
{
    if( e.type == SDL_WINDOWEVENT )
    {
        bool updateCaption = false;

        switch( e.window.event )
        {

        case SDL_WINDOWEVENT_SIZE_CHANGED:
            width = e.window.data1;
            height = e.window.data2;
            SDL_RenderPresent( renderer );
            break;

        //Repaint on exposure
        case SDL_WINDOWEVENT_EXPOSED:
            SDL_RenderPresent( renderer );
            break;

        //Mouse entered window
        case SDL_WINDOWEVENT_ENTER:
            mouseFocus = true;
            updateCaption = true;
            break;

        //Mouse left window
        case SDL_WINDOWEVENT_LEAVE:
            mouseFocus = false;
            updateCaption = true;
            break;

        //Window has keyboard focus
        case SDL_WINDOWEVENT_FOCUS_GAINED:
            keyboardFocus = true;
            updateCaption = true;
            break;

        //Window lost keyboard focus
        case SDL_WINDOWEVENT_FOCUS_LOST:
            keyboardFocus = false;
            updateCaption = true;
            break;

        //Window minimized
        case SDL_WINDOWEVENT_MINIMIZED:
            minimized = true;
            break;

        //Window maxized
        case SDL_WINDOWEVENT_MAXIMIZED:
            minimized = false;
            break;

        //Window restored
        case SDL_WINDOWEVENT_RESTORED:
            minimized = false;
            break;
        }

        //Update window caption with new data
        if( updateCaption )
        {
            std::stringstream caption;
            caption << "SDL Tutorial - MouseFocus:" << ( ( mouseFocus ) ? "On" : "Off" ) << " KeyboardFocus:" << ( ( keyboardFocus ) ? "On" : "Off" );
            SDL_SetWindowTitle( window, caption.str().c_str() );
        }
    }
    //Enter exit full screen on return key
    else if( e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN )
    {
        if( fullScreen )
        {
            SDL_SetWindowFullscreen( window, SDL_FALSE );
            fullScreen = false;
        }
        else
        {
            SDL_SetWindowFullscreen( window, SDL_TRUE );
            fullScreen = true;
            minimized = false;
        }
    }
}

void Window::free()
{
    if( window != NULL )
    {
        SDL_DestroyWindow( window );
    }

    mouseFocus = false;
    keyboardFocus = false;
    width = 0;
    height = 0;
}

int Window::getWidth()
{
    return width;
}

int Window::getHeight()
{
    return height;
}

bool Window::hasMouseFocus()
{
    return mouseFocus;
}

bool Window::hasKeyboardFocus()
{
    return keyboardFocus;
}

bool Window::isMinimized()
{
    return minimized;
}

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

        if( !window.init() )
        {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            renderer = window.createRenderer();
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
            }
        }
    }

    return success;
}

bool loadMedia()
{
    bool success = true;

    if( !sceneTexture.loadFromFile( "window.png" ) )
    {
        printf( "Failed to load window texture!\n" );
        success = false;
    }

    return success;
}

void close()
{
    sceneTexture.free();

    SDL_DestroyRenderer( renderer );
    window.free();

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
            SDL_Event e;
            for( ;; )
            {
                while( SDL_PollEvent( &e ) != 0 )
                {
                    if( e.type == SDL_QUIT )
                        SDL_Quit();

                    window.handleEvent( e );
                }

                if( !window.isMinimized() )
                {
                    SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
                    SDL_RenderClear( renderer );

                    //Render text textures
                    sceneTexture.render( ( window.getWidth() - sceneTexture.getWidth() ) / 2, ( window.getHeight() - sceneTexture.getHeight() ) / 2 );

                    SDL_RenderPresent( renderer );
                }
            }
        }
    }

    close();

    return 0;
}
