#include "global.h"

class Map_editor
{
    SDL_Texture* texture;
    SDL_Rect sizes;
    SDL_Rect* rect;

    Uint16 counter;
    fstream file;

public:
    Map_editor();
    ~Map_editor();

    bool loadMedia();
    void loadFile();
    void saveFile( SDL_Point point );

    void render( SDL_Rect ball, Uint8 &state );
    void render_edit_mode( SDL_Point point );
    void delete_block( int position );

    void close();
};
