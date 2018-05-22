#ifndef WALL_H
#define WALL_H

#include <SDL.h>
#include <string>
#include <fstream>

class Wall
{
    std::fstream file;
    SDL_Rect* rect;

    Uint16 number;
    Uint16 counter;

    SDL_Point point;
    SDL_Rect dstrect;

public:

    Wall();
    ~Wall();

    int fastAtoi( std::string &path );
    SDL_Rect setRect( std::string &path );

    void add( SDL_Renderer* &renderer, SDL_Event &e );
    void load();
    void save();
    void render( SDL_Renderer* &renderer );
    SDL_Rect getRect( SDL_Rect _rect );

};


#endif // WALL_H
