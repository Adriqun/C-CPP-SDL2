#ifndef CORE_H
#define CORE_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

class Core
{

public:

    bool initSDL( Uint32 flags = SDL_INIT_EVERYTHING );
    bool initIMG( int flags = IMG_INIT_PNG );
    bool initMIX( int frequency = 44100, Uint16 format = MIX_DEFAULT_FORMAT, int channels = 2, int chunksize = 2048 );
    bool initTTF();
};

#endif // CORE_H
