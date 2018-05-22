#include "chart.h"
#include <cstring>
#include <SDL_image.h>

Chart::Chart()
{
    width = 128;
    height = 128;

    texture = NULL;
    rect = NULL;
    counter = NULL;
    file = NULL;

    total = 14;
    type = 0;

    block.w = width;
    block.h = height;
    block.x = 0;
    block.y = 0;

    point.x = 0;
    point.y = 0;
}

void Chart::free()
{
    if( texture != NULL )
    {
        delete [] texture;
        texture = NULL;
    }

    if( rect != NULL )
    {
        delete [] rect;
        rect = NULL;
    }

    if( counter != NULL )
    {
        delete [] counter;
        counter = NULL;
    }

    if( file != NULL )
    {
        fclose( file );
        file = NULL;
    }

    block.x = 0;
    block.y = 0;
}



std::string Chart::intToString( int path )
{
    std::string tmp;
    if( path < 0 )
    {
        tmp = "-";
        path = -path;
    }
    if( path > 9 )
        tmp += intToString( path / 10 );

    tmp += path % 10 + 48;

    return tmp;
}

int Chart::stringToInt( std::string &path )
{
    int num = 0, buf;

    for( Uint8 i = 0 ; i < path.size(); i++ )
    {
        if( path[ i ] == '-' )
            i ++;

        buf = static_cast < int > ( path[ i ] ) - 48;
        for( Uint8 j = 1; j < path.size() - i; j ++ )
            buf *= 10;
        num += buf;
    }

    if( path[ 0 ] == '-')
    {
        num *= -1;
    }

    return num;
}

void Chart::setRect( std::string &path )
{
    std::string bufor;
    int nr = 0;

    for( Uint8 k = 0; k < path.size(); k++ )
    {
        if( path[ k ] == '.' )
        {
            nr = stringToInt( bufor );
            bufor = "";

            for( Uint8 i = k + 1; i < path.size(); i++ )
            {
                if( path[ i ] == '.' )
                {
                    rect[ nr ][ counter[ nr ] ].x = stringToInt( bufor ) + point.x;
                    bufor = "";

                    for( Uint8 j = i + 1; i < path.size(); j++ )
                    {
                        if( path[ j ] == '.' )
                        {
                            rect[ nr ][ counter[ nr ] ].y = stringToInt( bufor );
                            rect[ nr ][ counter[ nr ] ].w = width;
                            rect[ nr ][ counter[ nr ] ].h = height;
                            break;
                        }
                        bufor += path[ j ];
                    }
                    break;
                }
                bufor += path[ i ];
            }
            break;
        }
        bufor += path[ k ];
    }
    counter[ nr ]++;
}

void Chart::setCounter( std::string &path )
{
    std::string bufor;
    for( Uint8 k = 0; k < path.size(); k++ )
    {
        if( path[ k ] == '.' )
        {
            counter[ stringToInt( bufor ) ] ++;
            break;
        }

        bufor += path[ k ];
    }
}



void Chart::loadFile() // ustawia liczniki i prostokaty ( rect ) z pliku
{
    char bufor[ 22 ];
    std::string line;

    file = fopen( "wall/map.txt", "r" );
    if( file == NULL )
    {
        deb::loadingFileError( "wall/map.txt" );
    }
    else
    {
        while( !feof( file ) )
        {
            if( fgets( bufor, 20, file ) )
            {
                line = bufor;
                setCounter( line );
            }
        }

        for( Uint16 i = 0; i < total; i++ )
        {
            delete [] rect[ i ];
            rect[ i ] = NULL;
        }

        // alokujemy miejsce na ilosc blokow danego rodzaju w pamieci
        for( Uint16 i = 0; i < total; i++ )
        {
            rect[ i ] = new SDL_Rect [ counter[ i ] ];
            counter[ i ] = 0;
        }

    }
    fclose( file );
    file = NULL;

    file = fopen( "wall/map.txt", "r" );
    if( file == NULL )
    {
        deb::loadingFileError( "wall/map.txt" );
    }
    else
    {
        while( !feof( file ) )
        {
            if( fgets( bufor, 20, file ) )
            {
                line = bufor;
                setRect( line );
            }
        }
    }
    fclose( file );
    file = NULL;
}

SDL_Texture* Chart::loadTexture( SDL_Renderer* &renderer, std::string path )
{
    SDL_Surface* surface = IMG_Load( path.c_str() );
    SDL_Texture* newTexture = NULL;
    if( surface == NULL )
    {
        deb::loadingSurfaceError( path );
    }
    else
    {
        newTexture = SDL_CreateTextureFromSurface( renderer, surface );
        if( newTexture == NULL )
        {
            deb::createTextureFromSurfaceError( path );
        }

        SDL_FreeSurface( surface );
    }

    return newTexture;
}

void Chart::load( SDL_Renderer* &renderer )
{
    free();
    texture = new SDL_Texture* [ total ];
    rect = new SDL_Rect* [ total ];
    counter = new Uint16 [ total ];

    for( Uint16 i = 0; i < total; i++ )
    {
        texture[ i ] = NULL;

        texture[ i ] = loadTexture( renderer, "wall/" + intToString( i ) + ".png" );
        if( texture[ i ] == NULL )
        {
            deb::setTextureError();
        }

        counter[ i ] = 0;
    }

    loadFile();
}



void Chart::render( SDL_Renderer* &renderer, SDL_Point _point )
{
    for( Uint16 i = 0; i < total; i++ )
    {
        for( Uint16 j = 0; j < counter[ i ]; j++ )
        {
            if( point.x != _point.x )
            {
                rect[ i ][ j ].x += ( _point.x - point.x );
            }

            SDL_RenderCopy( renderer, texture[ i ], NULL, &rect[ i ][ j ] );
        }
    }
    point.x = _point.x;
}

void Chart::addToFile()
{
    char bufor[ 20 ];

    file = fopen( "wall/map.txt", "a" );
    if( file == NULL )
    {
        deb::loadingFileError( "map.txt" );
    }
    else
    {
        std::string line;
        line += intToString( type ) + '.' + intToString( block.x - point.x ) + '.' + intToString( block.y ) + ".\n";
        printf( "%s", line.c_str() );
        strcpy( bufor, line.c_str() );
        fputs( bufor, file );
    }
    fclose( file );
    file = NULL;

    loadFile();
}

void Chart::setMousePosition()
{
    if( type > 2 )
    {
        for( int i = 1; i < 10; i++ )
        {
            if( block.x < i * 128 )
            {
                block.x = ( i - 1 ) * 128;
                break;
            }
        }

        for( int i = 1; i < 10; i++ )
        {
            if( block.y < i * 128 )
            {
                block.y = ( i - 1 ) * 128;
                break;
            }
        }
    }
}

void Chart::controlEditMode( SDL_Event &e )
{
    const Uint8* key = SDL_GetKeyboardState( NULL );

    if( e.type == SDL_MOUSEMOTION )
    {
        SDL_GetMouseState( &block.x, &block.y );
        setMousePosition();
    }
    else if( e.type == SDL_MOUSEBUTTONDOWN )
    {
        SDL_GetMouseState( &block.x, &block.y );
        setMousePosition();

        addToFile();
        SDL_Delay( 200 );
    }

    if( key[ SDL_SCANCODE_RIGHT ] )
    {
        point.x -= 1024;
        for( Uint16 i = 0; i < total; i++ )
        {
            for( Uint16 j = 0; j < counter[ i ]; j++ )
            {
                rect[ i ][ j ].x -= 1024;
            }
        }

        SDL_Delay( 200 );
    }
    else if( key[ SDL_SCANCODE_LEFT ] )
    {
        point.x += 1024;
        for( Uint16 i = 0; i < total; i++ )
        {
            for( Uint16 j = 0; j < counter[ i ]; j++ )
            {
                rect[ i ][ j ].x += 1024;
            }
        }

        SDL_Delay( 200 );
    }
    else if( key[ SDL_SCANCODE_X ] )
    {
        if( type == total -1 )
            type = 0;
        else
            type ++;

        SDL_Delay( 100 );
    }
    else if( key[ SDL_SCANCODE_Z ] )
    {
        if( type == 0 )
            type = total -1;
        else
            type --;

        SDL_Delay( 100 );
    }
}

void Chart::renderEditMode( SDL_Renderer* &renderer )
{
    for( Uint16 i = 0; i < total; i++ )
    {
        for( Uint16 j = 0; j < counter[ i ]; j++ )
        {
            SDL_RenderCopy( renderer, texture[ i ], NULL, &rect[ i ][ j ] );
        }
    }

    SDL_RenderCopy( renderer, texture[ type ], NULL, &block );
    SDL_SetRenderDrawColor( renderer, 82, 82, 82, 0xFF );
}

bool Chart::checkCollision( SDL_Rect a )
{
    a.h -= 30;
    a.w -= 2;
    a.x -= 2;
    for( Uint16 i = 6; i < total; i ++ )
    {
        for( Uint16 j = 0; j < counter[ i ]; j ++ )
        {
            if( a.y + a.h >= rect[ i ][ j ].y && a.y <= rect[ i ][ j ].y + rect[ i ][ j ].h )
            {
                if( a.x + a.w >= rect[ i ][ j ].x && a.x <= rect[ i ][ j ].x + rect[ i ][ j ].w )
                {
                    return true;
                }
            }
        }
    }

    return false;
}



Wall::Wall()
{
    texture = NULL;

    rect.x = 0;
    rect.y = 0;
    rect.w = 0;
    rect.h = 0;
    vel = 6;
}

Wall::~Wall()
{
    free();
}

void Wall::free()
{
    if( texture != NULL )
    {
        SDL_DestroyTexture( texture );
        texture = NULL;

        rect.x = 0;
        rect.y = 0;
        rect.w = 0;
        rect.h = 0;
    }
}

void Wall::loadTexture( SDL_Renderer* &renderer, char* path )
{
    SDL_Surface* surface = IMG_Load( path );
    if( surface == NULL )
    {
        deb::loadingSurfaceError( path );
    }
    else
    {
        texture = SDL_CreateTextureFromSurface( renderer, surface );
        if( texture == NULL )
        {
            deb::createTextureFromSurfaceError( path );
        }
        else
        {
            rect.w = surface->w;
            rect.h = surface->h;
        }

        SDL_FreeSurface( surface );
    }
}

void Wall::load( SDL_Renderer* &renderer )
{
    free();

    loadTexture( renderer, "wall/bg_white.png" );
    if( texture == NULL )
    {
        deb::setTextureError();
    }
}

void Wall::render( SDL_Renderer* &renderer, Uint8 motion )
{
    if( motion == 1 )
    {
        rect.x += vel;
    }
    if( motion == 2 )
    {
        rect.x -= vel;
    }

    if( rect.x <= rect.w * -1 )
    {
        rect.x = 0;
    }

    if( rect.x >= rect.w )
    {
        rect.x = 0;
    }


    SDL_RenderCopy( renderer, texture, NULL, &rect );

    rect.x += rect.w;
    SDL_RenderCopy( renderer, texture, NULL, &rect );
    rect.x -= rect.w;

    rect.x -= rect.w;
    SDL_RenderCopy( renderer, texture, NULL, &rect );
    rect.x += rect.w;
}
