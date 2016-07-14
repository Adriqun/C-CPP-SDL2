#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>

class Timer
{
    //czas w ktorym timer zaczal liczyc
    Uint32 startTicks;

    //czas w ktorym timer zakonczyl liczenie
    Uint32 pausedTicks;

    //aktualny status timera
    bool started;
    bool paused;

public:
    Timer();
    void start();
    void stop();
    void pause();
    void unpause();

    //aktualny czas timera
    Uint32 getTicks();

    //funkcje zwracajace status timera
    bool isStarted();
    bool isPaused();
};

class Texture
{
    SDL_Texture* texture;
    int width;
    int height;

public:
    Texture();
    ~Texture();
    bool loadFromFile( std::string path, SDL_Renderer* &renderer );

#ifdef _SDL_TTF_H
    bool loadFromRenderedText( std::string textureText, SDL_Color textColor, TTF_Font* &font, SDL_Renderer* &renderer );
#endif

    void free();
    void setColor( Uint8 red, Uint8 green, Uint8 blue );
    void setBlendMode( SDL_BlendMode blending );
    void setAlpha( Uint8 alpha );
    void render( int x, int y, SDL_Renderer* &renderer, SDL_Rect* clip=NULL, double angle=0.0, SDL_Point* center = NULL, SDL_RendererFlip flip=SDL_FLIP_NONE);

    int getWidth();
    int getHeight();
};
