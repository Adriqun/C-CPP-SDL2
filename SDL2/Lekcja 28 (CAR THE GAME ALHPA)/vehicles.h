#include <SDL.h>

class Car
{
    int nr;
    SDL_Texture* texture;
    SDL_Rect* srcRect;
    const Uint8* key;

public:
    SDL_Rect dstRect;
    double angle;

    Car();
    ~Car();
    SDL_Texture* loadTexture(std::string path, SDL_Renderer* &renderer);
    bool loadMedia(SDL_Renderer* &renderer);
    void render(SDL_Renderer* &renderer);
    void close();
};
