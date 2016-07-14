#include <SDL.h>
#include <fstream>

class Map
{
    int WIDTH;
    int HEIGHT;
    SDL_Texture* texture;
    SDL_Rect* rect;
    std::fstream file;
    int nr;
    int nr_rect;

public:
    Map();
    ~Map();
    void collision(SDL_Rect &champ, SDL_Rect &coor, double &angle);

    SDL_Texture* loadTexture(std::string path, SDL_Renderer* &renderer);

    void setPosition(int x, int y);

    bool loadMedia(SDL_Renderer* &renderer);
    void render(SDL_Rect &champ, double &angle, SDL_Renderer* &renderer);
    void close();

};
