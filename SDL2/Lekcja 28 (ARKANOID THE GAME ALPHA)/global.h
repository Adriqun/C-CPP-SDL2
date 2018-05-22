#include <SDL.h>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <cstdlib>
#include <SDL_image.h>

using namespace std;

#ifndef GLOBAL_H
#define GLOBAL_H

extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern const Uint16 SCREEN_WIDTH;
extern const Uint16 SCREEN_HEIGHT;
extern int FRAME;

SDL_Texture* loadTexture( std::string path, SDL_Rect &rect );
bool init();
void shut();

#endif
