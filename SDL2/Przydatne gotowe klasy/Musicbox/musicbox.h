#ifndef MUSICBOX_H
#define MUSICBOX_H

#include <SDL_mixer.h>
#include <string>

class Chunk
{
    Mix_Chunk* chunk;

public:

    Chunk();
    ~Chunk();
    void free();

    bool loadChunk( std::string path );
    void setVolume( int volume );

    void play( int loops = 0 );
    void playTimed( int loops = 0, int ticks = 0 );

    void fadeIn( int loops = 0, int ms = 100 );
    void fadeOut( int ms = 100 );
};

class Music
{
    Mix_Music* music;

public:

    Music();
    ~Music();
    void free();

    bool loadMusic( std::string path );
    void setVolume( int volume );

    void play( int loops = 0 );
    void pause();
    void resume();

    Mix_MusicType getType();
    void fadeIn( int loops = 0, int ms = 100 );
    void fadeOut( int ms = 100 );

};

#endif // MUSICBOX_H
