#include "global.h"

class Floor
{

protected:
    SDL_Rect rect;
    SDL_Texture* texture;

public:
    Floor();
    ~Floor();
    bool loadMedia();
    void render( SDL_Rect &rectangle );
    void close();
};

class Ball :public Floor
{

public:
    bool loadMedia();

};
