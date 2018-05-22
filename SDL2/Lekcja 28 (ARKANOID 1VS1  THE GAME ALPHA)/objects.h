#include "global.h"

class Board
{
protected:
    SDL_Texture* texture;
    SDL_Rect rect;

public:

    Board();
    ~Board();
    bool load( string path );
    void render( SDL_Rect &rectangle );
    void close();
};

class Background :public Board
{
public:
    void render();
};

class Ball :public Board{};

class Button :public Board{};
