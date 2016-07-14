#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <iostream>

using namespace std;

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern int FRAME;

bool init();
SDL_Texture* loadTexture( string path , SDL_Rect &rect );
