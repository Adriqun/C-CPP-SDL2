#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL.h>
#include <string>

class Texture
{
    Uint8 cage, slow, offset;
    Uint16 width, height;
    SDL_Texture* texture;
    SDL_Rect** rect;

    double angle;
    SDL_Point* center;
    SDL_RendererFlip flip;

public:

    Texture( Uint8 c );
    ~Texture();

    Uint16 getWidth();
    Uint16 getHeight();

    void setSlow( Uint8 s );
    void setOffset( Uint8 off );
    void runOffset( Uint8 startLoop, Uint8 endLoop );

    void setFlip( SDL_RendererFlip f );
    void setAngle( double a );
    void setCenter( SDL_Point* c );

    void setAlpha( Uint8 a );
    void setBlendMode( SDL_BlendMode b );
    void setColor( Uint8 r, Uint8 g, Uint8 b );
    void setTexture( SDL_Renderer* &renderer, std::string path );

    void render( SDL_Renderer* &renderer, SDL_Rect* &dstRect );
};

#endif // TEXTURE_H
