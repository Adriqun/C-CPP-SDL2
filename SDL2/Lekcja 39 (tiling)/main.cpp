#include <fstream>
#include "texture.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int LEVEL_WIDTH = 1280;
const int LEVEL_HEIGHT = 960;

//Tile constants
const int TILE_WIDTH = 80;
const int TILE_HEIGHT = 80;
const int TOTAL_TILES = 192;
const int TOTAL_TILE_SPRITES = 12;

//The different tile sprites
const int TILE_RED = 0;
const int TILE_GREEN = 1;
const int TILE_BLUE = 2;
const int TILE_CENTER = 3;
const int TILE_TOP = 4;
const int TILE_TOPRIGHT = 5;
const int TILE_RIGHT = 6;
const int TILE_BOTTOMRIGHT = 7;
const int TILE_BOTTOM = 8;
const int TILE_BOTTOMLEFT = 9;
const int TILE_LEFT = 10;
const int TILE_TOPLEFT = 11;

class Tile
{
public:
    //Initializes position and type
    Tile( int x, int y, int tileType );

    //Shows the tile
    void render( SDL_Rect& camera );

    //Get the tile type
    int getType();

    //Get the collision box
    SDL_Rect getBox();

private:
    //The attributes of the tile
    SDL_Rect box;
    int type;
};

class Dot
{
    SDL_Rect box;
    int velX, velY;

public:
    static const int DOT_WIDTH = 20;
    static const int DOT_HEIGHT = 20;
    static const int DOT_VEL = 10;
    Dot();

    void handleEvent( SDL_Event& e );
    void move( Tile *tiles[] );
    void setCamera( SDL_Rect& camera );
    void render( SDL_Rect& camera );
};

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

//Scene textures
Texture dotTexture;
Texture tileTexture;
SDL_Rect tileClips[ TOTAL_TILE_SPRITES ];

bool init()
{
    bool success = true;

    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        {
            printf( "Warning: Linear texture filtering not enabled!" );
        }

        window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( window == NULL )
        {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
            if( renderer == NULL )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else
            {
                SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
                if( !( IMG_Init( IMG_INIT_PNG ) & IMG_INIT_PNG ) )
                {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                    success = false;
                }
            }
        }
    }

    return success;
}

bool setTiles( Tile* tiles[] )
{
    //Success flag
    bool tilesLoaded = true;

    //The tile offsets
    int x = 0, y = 0;

    //Open the map
    std::ifstream map( "lazy.map" );

    //If the map couldn't be loaded
    if( map == NULL )
    {
        printf( "Unable to load map file!\n" );
        tilesLoaded = false;
    }
    else
    {
        //Initialize the tiles
        for( int i = 0; i < TOTAL_TILES; ++i )
        {
            //Determines what kind of tile will be made
            int tileType = -1;

            //Read tile from map file
            map >> tileType;

            //If the was a problem in reading the map
            if( map.fail() )
            {
                //Stop loading map
                printf( "Error loading map: Unexpected end of file!\n" );
                tilesLoaded = false;
                break;
            }

            //If the number is a valid tile number
            if( ( tileType >= 0 ) && ( tileType < TOTAL_TILE_SPRITES ) )
            {
                tiles[ i ] = new Tile( x, y, tileType );
            }
            //If we don't recognize the tile type
            else
            {
                //Stop loading map
                printf( "Error loading map: Invalid tile type at %d!\n", i );
                tilesLoaded = false;
                break;
            }

            //Move to next tile spot
            x += TILE_WIDTH;

            //If we've gone too far
            if( x >= LEVEL_WIDTH )
            {
                //Move back
                x = 0;

                //Move to the next row
                y += TILE_HEIGHT;
            }
        }

        //Clip the sprite sheet
        if( tilesLoaded )
        {
            tileClips[ TILE_RED ].x = 0;
            tileClips[ TILE_RED ].y = 0;
            tileClips[ TILE_RED ].w = TILE_WIDTH;
            tileClips[ TILE_RED ].h = TILE_HEIGHT;

            tileClips[ TILE_GREEN ].x = 0;
            tileClips[ TILE_GREEN ].y = 80;
            tileClips[ TILE_GREEN ].w = TILE_WIDTH;
            tileClips[ TILE_GREEN ].h = TILE_HEIGHT;

            tileClips[ TILE_BLUE ].x = 0;
            tileClips[ TILE_BLUE ].y = 160;
            tileClips[ TILE_BLUE ].w = TILE_WIDTH;
            tileClips[ TILE_BLUE ].h = TILE_HEIGHT;

            tileClips[ TILE_TOPLEFT ].x = 80;
            tileClips[ TILE_TOPLEFT ].y = 0;
            tileClips[ TILE_TOPLEFT ].w = TILE_WIDTH;
            tileClips[ TILE_TOPLEFT ].h = TILE_HEIGHT;

            tileClips[ TILE_LEFT ].x = 80;
            tileClips[ TILE_LEFT ].y = 80;
            tileClips[ TILE_LEFT ].w = TILE_WIDTH;
            tileClips[ TILE_LEFT ].h = TILE_HEIGHT;

            tileClips[ TILE_BOTTOMLEFT ].x = 80;
            tileClips[ TILE_BOTTOMLEFT ].y = 160;
            tileClips[ TILE_BOTTOMLEFT ].w = TILE_WIDTH;
            tileClips[ TILE_BOTTOMLEFT ].h = TILE_HEIGHT;

            tileClips[ TILE_TOP ].x = 160;
            tileClips[ TILE_TOP ].y = 0;
            tileClips[ TILE_TOP ].w = TILE_WIDTH;
            tileClips[ TILE_TOP ].h = TILE_HEIGHT;

            tileClips[ TILE_CENTER ].x = 160;
            tileClips[ TILE_CENTER ].y = 80;
            tileClips[ TILE_CENTER ].w = TILE_WIDTH;
            tileClips[ TILE_CENTER ].h = TILE_HEIGHT;

            tileClips[ TILE_BOTTOM ].x = 160;
            tileClips[ TILE_BOTTOM ].y = 160;
            tileClips[ TILE_BOTTOM ].w = TILE_WIDTH;
            tileClips[ TILE_BOTTOM ].h = TILE_HEIGHT;

            tileClips[ TILE_TOPRIGHT ].x = 240;
            tileClips[ TILE_TOPRIGHT ].y = 0;
            tileClips[ TILE_TOPRIGHT ].w = TILE_WIDTH;
            tileClips[ TILE_TOPRIGHT ].h = TILE_HEIGHT;

            tileClips[ TILE_RIGHT ].x = 240;
            tileClips[ TILE_RIGHT ].y = 80;
            tileClips[ TILE_RIGHT ].w = TILE_WIDTH;
            tileClips[ TILE_RIGHT ].h = TILE_HEIGHT;

            tileClips[ TILE_BOTTOMRIGHT ].x = 240;
            tileClips[ TILE_BOTTOMRIGHT ].y = 160;
            tileClips[ TILE_BOTTOMRIGHT ].w = TILE_WIDTH;
            tileClips[ TILE_BOTTOMRIGHT ].h = TILE_HEIGHT;
        }
    }

    //Close the file
    map.close();

    //If the map was loaded fine
    return tilesLoaded;
}

bool loadMedia( Tile* tiles[] )
{
    bool success = true;

    if( !dotTexture.loadFromFile( renderer, "dot.bmp" ) )
    {
        printf( "Failed to load dot texture!\n" );
        success = false;
    }

    if( !tileTexture.loadFromFile( renderer, "tiles.png" ) )
    {
        printf( "Failed to load tile set texture!\n" );
        success = false;
    }

    if( !setTiles( tiles ) )
    {
        printf( "Failed to load tile set!\n" );
        success = false;
    }

    return success;
}

void close( Tile* tiles[] )
{
    for( int i = 0; i < TOTAL_TILES; ++i )
    {
        if( tiles[ i ] == NULL )
        {
            delete tiles[ i ];
            tiles[ i ] = NULL;
        }
    }

    dotTexture.free();
    tileTexture.free();

    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    window = NULL;
    renderer = NULL;

    IMG_Quit();
    SDL_Quit();
}

bool checkCollision( SDL_Rect a, SDL_Rect b )
{
    if( a.y + a.h <= b.y )  return false;
    if( a.y >= b.y + b.h )  return false;
    if( a.x + a.w <= b.x )  return false;
    if( a.x >= b.x + b.w )  return false;
    return true;
}

bool touchesWall( SDL_Rect box, Tile* tiles[] )
{
    //Go through the tiles
    for( int i = 0; i < TOTAL_TILES; ++i )
    {
        //If the tile is a wall type tile
        if( ( tiles[ i ]->getType() >= TILE_CENTER ) && ( tiles[ i ]->getType() <= TILE_TOPLEFT ) )
        {
            //If the collision box touches the wall tile
            if( checkCollision( box, tiles[ i ]->getBox() ) )
            {
                return true;
            }
        }
    }

    //If no wall tiles were touched
    return false;
}

Tile::Tile( int x, int y, int tileType )
{
    box.x = x;
    box.y = y;
    box.w = TILE_WIDTH;
    box.h = TILE_HEIGHT;

    type = tileType;
}

void Tile::render( SDL_Rect& camera )
{
    if( checkCollision( camera, box ) )
    {
        tileTexture.render( renderer, box.x - camera.x, box.y - camera.y, &tileClips[ type ] );
    }
}

int Tile::getType()
{
    return type;
}

SDL_Rect Tile::getBox()
{
    return box;
}

Dot::Dot()
{
    box.x = 0;
    box.y = 0;
    box.w = DOT_WIDTH;
    box.h = DOT_HEIGHT;

    velX = 0;
    velY = 0;
}

void Dot::handleEvent( SDL_Event& e )
{
    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        switch( e.key.keysym.sym )
        {
        case SDLK_UP:   velY -= DOT_VEL;    break;
        case SDLK_DOWN: velY += DOT_VEL;    break;
        case SDLK_LEFT: velX -= DOT_VEL;    break;
        case SDLK_RIGHT:velX += DOT_VEL;    break;
        }
    }
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        switch( e.key.keysym.sym )
        {
        case SDLK_UP:   velY += DOT_VEL;    break;
        case SDLK_DOWN: velY -= DOT_VEL;    break;
        case SDLK_LEFT: velX += DOT_VEL;    break;
        case SDLK_RIGHT:velX -= DOT_VEL;    break;
        }
    }
}

void Dot::move( Tile *tiles[] )
{
    box.x += velX;

    //If the dot went too far to the left or right or touched a wall
    if( ( box.x < 0 ) || ( box.x + DOT_WIDTH > LEVEL_WIDTH ) || touchesWall( box, tiles ) )
    {
        box.x -= velX;
    }

    box.y += velY;

    //If the dot went too far up or down or touched a wall
    if( ( box.y < 0 ) || ( box.y + DOT_HEIGHT > LEVEL_HEIGHT ) || touchesWall( box, tiles ) )
    {
        box.y -= velY;
    }
}

void Dot::setCamera( SDL_Rect& camera )
{
    //Center the camera over the dot
    camera.x = ( box.x + DOT_WIDTH / 2 ) - SCREEN_WIDTH / 2;
    camera.y = ( box.y + DOT_HEIGHT / 2 ) - SCREEN_HEIGHT / 2;

    //Keep the camera in bounds
    if( camera.x < 0 )                          camera.x = 0;
    if( camera.y < 0 )                          camera.y = 0;
    if( camera.x > LEVEL_WIDTH - camera.w )     camera.x = LEVEL_WIDTH - camera.w;
    if( camera.y > LEVEL_HEIGHT - camera.h )    camera.y = LEVEL_HEIGHT - camera.h;
}

void Dot::render( SDL_Rect& camera )
{
    dotTexture.render( renderer, box.x - camera.x, box.y - camera.y );
}

int main( int argc, char* args[] )
{
    if( !init() )
        printf( "Failed to initialize!\n" );
    else
    {
        //The level tiles
        Tile* tileSet[ TOTAL_TILES ];

        //Load media
        if( !loadMedia( tileSet ) )
            printf( "Failed to load media!\n" );
        else
        {

            SDL_Event e;
            Dot dot;

            //Level camera
            SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

            for( ;; )
            {
                while( SDL_PollEvent( &e ) != 0 )
                {
                    if( e.type == SDL_QUIT )
                        close( tileSet );

                    dot.handleEvent( e );
                }

                dot.move( tileSet );
                dot.setCamera( camera );

                SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
                SDL_RenderClear( renderer );

                for( int i = 0; i < TOTAL_TILES; ++i )
                    tileSet[ i ]->render( camera );

                dot.render( camera );
                SDL_RenderPresent( renderer );
            }
        }

        close( tileSet );
    }

    return 0;
}
