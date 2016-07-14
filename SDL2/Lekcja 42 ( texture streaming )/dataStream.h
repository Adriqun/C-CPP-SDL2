#ifndef DATASTREAM_H
#define DATASTREAM_H

#include "texture.h"

class DataStream
{
    SDL_Surface* images[ 4 ];
    int currentImage;
    int mDelayFrames;

public:
    DataStream();

    //Loads initial data
    bool loadMedia();

    //Deallocator
    void free();

    //Gets current frame data
    void* getBuffer();
};

#endif // DATASTREAM_H
