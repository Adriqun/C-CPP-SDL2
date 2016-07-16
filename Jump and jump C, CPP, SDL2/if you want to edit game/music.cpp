#include "music.h"
#include <stdio.h>

Music::Music()
{
    music = NULL;
}

Music::~Music()
{
    free();
}


void Music::free()
{
    if( music != NULL )
    {
        Mix_FreeMusic( music );
        music = NULL;
    }
}

bool Music::load( const char* path, int volume )
{
    bool success = true;

    free();

    music = Mix_LoadMUS( path );
    if( music == NULL )
    {
        printf( "Not found music %s\n", path );
        printf( "Error %s\n", Mix_GetError() );
        success = false;
    }
    else if( volume != 0 )
    {
        Mix_VolumeMusic( volume );
    }

    return success;
}


void Music::play()
{
    if( Mix_PausedMusic() == 1 )
        Mix_ResumeMusic();

    if( Mix_PlayingMusic() == 0 )
    {
        Mix_PlayMusic( music, -1 );
    }
}

void Music::pause()
{
    if( Mix_PausedMusic() == 1 )
        Mix_ResumeMusic();
    else
        Mix_PauseMusic();
}

void Music::halt()
{
    Mix_HaltMusic();
}


Mix_Music* Music::getChunk()
{
    return music;
}
