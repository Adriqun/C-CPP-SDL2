#ifndef CORE_H
#define CORE_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <string>
#include <stdio.h>
#include <string>

namespace core
{
    bool init();
    void close_basic( SDL_Renderer* &renderer, SDL_Window* &window );
    void draw_basic( SDL_Renderer* &renderer );
    bool create_window( SDL_Window* &window, uint16_t width, uint16_t height );
    bool create_renderer( SDL_Renderer* &renderer, SDL_Window* &window );

    SDL_Texture* load_tex( SDL_Renderer* &renderer, std::string path );
    SDL_Texture* load_tex_re( SDL_Renderer* &renderer, std::string path, SDL_Rect &rect );
    SDL_Texture* load_tex_re_sc( SDL_Renderer* &renderer, std::string path, SDL_Rect &rect, uint8_t w, uint8_t h );

    Mix_Music* load_music( std::string path );
    Mix_Chunk* load_chunk( std::string path );

    SDL_Texture* load_fr_re_text( SDL_Renderer* &renderer, std::string path, SDL_Color &color, TTF_Font* &font );
    TTF_Font* load_font( std::string path, uint8_t _size );
}

#endif // CORE_H
