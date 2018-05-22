#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

class Dot
{
    SDL_Texture* doot;

    int WIDTH;
    int HEIGHT;
    const Uint8* key;
    int speed;

public:
    SDL_Rect rect;
    Dot();
    ~Dot();
    SDL_Texture* loadTexture(std::string path, SDL_Renderer* &renderer);
    bool loadMedia(SDL_Renderer* &renderer);
    void present(SDL_Renderer* &renderer);
    void close();

};
