#pragma once

#include <SDL_mixer.h>

class Music
{
    Mix_Music* music;

public:

    Music();
    ~Music();

    void free();
    bool load( const char* path, int volume = 0 );

    void play();
    void pause();
    void halt();

    Mix_Music* getChunk();
};
