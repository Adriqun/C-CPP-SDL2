#ifndef MAP_EDITOR_H
#define MAP_EDITOR_H

#include <SDL.h>
#include <fstream>

class Chart
{
    std::fstream file;
    SDL_Texture** texture;
    SDL_Rect** arect;
    SDL_Rect** brect;
    uint8_t type;
    SDL_Point point;

public:
    uint8_t how_many;
    uint16_t* counter;

    Chart();
    ~Chart();
    void close();

    void load_texture( SDL_Texture* _texture );

    // do edytora mapy
    int string_to_int( std::string path );
    void set_rect( SDL_Rect &rect, std::string &draft );
    void load_file();
    void add_to_file( std::string data );
    void draw_block( SDL_Renderer* &renderer, SDL_Point point, uint8_t type );

    // mapa
    void draw( SDL_Renderer* &renderer, SDL_Rect _rect );
    SDL_Rect get_rect( uint16_t i, uint16_t j );
};


#endif // MAP_EDITOR_H
