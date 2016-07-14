#ifndef PIXEL_DETECTOR_H
#define PIXEL_DETECTOR_H

#include <SDL.h>
#include <string>
#include <fstream>

class PixelDetector
{
    std::fstream file;
    std::string series;

public:

    std::string intToString( int path );
    int stringToInt( std::string path );

    void addToFile( SDL_Texture* &t, SDL_Surface* &s );
    bool loadTexture( SDL_Renderer* &renderer, std::string path );
    void load( SDL_Renderer* &renderer, std::string path, int range );

    std::string getSeries();
};

#endif // PIXEL_DETECTOR_H
