#include "musicbox.h"
#include <stdio.h>

Chunk::Chunk()
{
    chunk = NULL;
}

Chunk::~Chunk()
{
    free();
}

void Chunk::free()
{
    if( chunk != NULL )
    {
        Mix_FreeChunk( chunk );
        chunk = NULL;
    }
}

bool Chunk::loadChunk( std::string path )
{
    chunk = Mix_LoadWAV( path.c_str() );

    if( chunk == NULL )
    {
        printf( "Nie wczytano kawa³ka! Error %s\n", Mix_GetError() );
    }

    return chunk != NULL;
}

void Chunk::setVolume( int volume )
{
    Mix_VolumeChunk( chunk, volume );
}

void Chunk::play( int loops )
{
    Mix_PlayChannel( -1, chunk, loops );
}

void Chunk::playTimed( int loops, int ticks )
{
    Mix_PlayChannelTimed( -1, chunk, loops, ticks );
}

void Chunk::fadeIn( int loops, int ms )
{
    Mix_FadeInChannel( -1, chunk, loops, ms );
}

void Chunk::fadeOut( int ms )
{
    Mix_FadeOutChannel( -1, ms );
}




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

bool Music::loadMusic( std::string path )
{
    music = Mix_LoadMUS( path.c_str() );
    if( music != NULL )
    {
        printf( "Nie wczytano muzyki! Error %s\n", Mix_GetError() );
    }

    return music != NULL;
}

void Music::setVolume( int volume )
{
    Mix_VolumeMusic( volume );
}

void Music::play( int loops )
{
    if( Mix_PlayingMusic() == 0 )
    {
        Mix_PlayMusic( music, loops );
    }
}

void Music::pause()
{
    if( Mix_PlayingMusic() != 0 )
    {
        if( Mix_PausedMusic() != 1 )
        {
            Mix_PauseMusic();
        }
    }
}

void Music::resume()
{
    if( Mix_PlayingMusic() != 0 )
    {
        if( Mix_PausedMusic() == 1 )
        {
            Mix_ResumeMusic();
        }
    }
}

Mix_MusicType Music::getType()
{
    return Mix_GetMusicType( music );
}

void Music::fadeIn( int loops, int ms )
{
    Mix_FadeInMusic( music, loops, ms );
}

void Music::fadeOut( int ms )
{
    Mix_FadeOutMusic( ms );
}
