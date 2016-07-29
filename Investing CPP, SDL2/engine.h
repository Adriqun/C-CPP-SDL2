#include "title.h"
#include "goal.h"

class Engine
{
    bool quit;
    int width;
    int height;
    SDL_Event event;
    SDL_Window* window;
    SDL_Renderer* renderer;

    Title title;
    Texture title_bar;

    Goal goal;

public:

    Engine();
    ~Engine();
    void free();

    bool load();
    bool init();
    void loop();
    void close();
};
