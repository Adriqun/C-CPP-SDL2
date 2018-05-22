#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <fstream>
#include <cstdlib>

class Map
{
    SDL_Texture* rectangle;
    SDL_Rect rect;

    int WIDTH;
    int HEIGHT;

    int nr_block;
    int nr;
    SDL_Rect *block;

    std::fstream file;

public:
    Map();
    ~Map();
    SDL_Texture* loadTexture(std::string path, SDL_Renderer* &renderer);
    void collision(SDL_Rect &champ, SDL_Rect &coor);
    void setPosition(int x, int y);
    bool loadMedia(SDL_Renderer* &renderer);
    void present(SDL_Renderer* &renderer);
    void show(SDL_Renderer* &renderer, SDL_Rect &champ);
    void close();
};
