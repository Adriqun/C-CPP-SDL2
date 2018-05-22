#pragma once

#include <SDL_mixer.h>

class Chunk
{
    Mix_Chunk* chunk;

public:

    Chunk();
    ~Chunk();
    void free();

    bool load( const char* path, int volume = 0 );
    void play();

    Mix_Chunk* get();
    void setVolume( int volume );
};
