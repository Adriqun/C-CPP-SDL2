#include "map_editor.h"

Map_editor::Map_editor()
{
    texture = NULL;
    rect = NULL;
    counter = 0;
}

Map_editor::~Map_editor()
{
    texture = NULL;
    rect = NULL;
}

bool Map_editor::loadMedia()
{
    texture = loadTexture( "skrzynka.png", sizes );

    if( texture == NULL )
    {
        printf( "Blad loadMedia(), texture!\n" );
        return false;
    }
    else
    {
        rect = new SDL_Rect [ 256 ];
        loadFile();
    }

    return true;
}

void Map_editor::loadFile()
{
    string line, bufor;
    Uint16 nr_line = 0;

    file.open( "bloki.txt", ios::in );

    while( getline( file, line ) )
    {
        bufor = " ";

        for( Uint8 i = 0; i<line.length() - 1; i++ )
        {
            if( line[ i ] == ' ' )
            {
                rect[ nr_line ].x = atoi( bufor.c_str() );

                bufor = " ";

                i++;

                for( Uint8 j = i; j<line.length(); j++ )
                {
                    bufor += line[ j ];
                }

                rect[ nr_line ].y = atoi( bufor.c_str() );

            }

            bufor += line[ i ];
        }

        rect[ nr_line ].w = sizes.w;
        rect[ nr_line ].h = sizes.h;

        nr_line++;
    }

    counter = nr_line;

    file.close();
}

void Map_editor::saveFile( SDL_Point point )
{
    //celowe opoznienie aby nie dalo sie dodac np 100 blokow w jedno kratke!
    SDL_Delay( 150 );

    file.open( "bloki.txt", ios::out | ios::app );

    //automatyczne celowanie :D
    for( Uint16 i = 0; i < 60; i++ )

        if( point.x < i * 50 )
        {
            point.x = i * 50 -50;
            break;
        }

    for( Uint16 i = 0; i < 60; i++ )
        if( point.y < i * 50 )
        {
            point.y = i * 50 -50;
            break;
        }

    file << point.x<< " " << point.y<< endl;
    //cout<<"X  "<<point.x<<"   Y  "<<point.y<<endl;
    file.close();
}

void Map_editor::delete_block( int position )
{

    string line[ 2000 ];
    int number = 0;

    //otwieramy plik i przepisujemy to co sie w nim znajduje i zamykamy
    file.open( "bloki.txt", ios::in );

    while( getline( file, line[ number ] ) )
        number++;

    file.close();
    line[ position ] = line[ number - 1 ];
    file.open( "bloki.txt", ios::out);

    for( int i = 0; i < number - 1; i++ )
    {
        file << line[ i ] << "\n";
    }

    file.close();
    loadFile();
}

void Map_editor::render( SDL_Rect ball, Uint8 &state )
{
    for( Uint8 i = 0; i < counter; i++ )
    {
        SDL_RenderCopy( renderer, texture, NULL, &rect[ i ] );

        //detektor kolizji *____* napisa³em ten algorytm w 2016 roku 21 stycznia btw dalej jestem z Ani¹ :D
        if( ball.x + ball.w > rect[ i ].x && ball.x + ball.w < rect[ i ].x + rect[ i ].w / 5 && ball.y + ball.h > rect[ i ].y && ball.y < rect[ i ].y + rect[ i ].h )
        {
            if( state == 2 )
                state = 4;
            else if( state == 1 )
                state = 3;
                delete_block( i );
        }
        else if( ball.x + ball.w > rect[ i ].x && ball.x + ball.w < rect[ i ].x + rect[ i ].w && ball.y + ball.h > rect[ i ].y && ball.y + ball.h < rect[ i ].y + rect[ i ].h / 5 )
        {
            if( state == 2 )
                state = 1;
            else if( state == 4 )
                state = 3;
                delete_block( i );
        }
        else if( ball.x + ball.w > rect[ i ].x + rect[ i ].w * 0.8 && ball.x + ball.w < rect[ i ].x + rect[ i ].w && ball.y + ball.h > rect[ i ].y && ball.y < rect[ i ].y + rect[ i ].h )
        {
            if( state == 4 )
                state = 2;
            else if( state == 3 )
                state = 1;
                delete_block( i );
        }
        else if( ball.x + ball.w > rect[ i ].x && ball.x + ball.w < rect[ i ].x + rect[ i ].w && ball.y > rect[ i ].y + rect[ i ].h * 0.8 && ball.y < rect[ i ].y + rect[ i ].h )
        {
            if( state == 1 )
                state = 2;
            else if( state == 3 )
                state = 4;
                delete_block( i );
        }
    }
}

void Map_editor::render_edit_mode( SDL_Point point )
{
    for( Uint8 i = 0; i < counter; i++ )
        SDL_RenderCopy( renderer, texture, NULL, &rect[ i ] );

    SDL_Rect bufor;
    bufor.w = sizes.w;
    bufor.h = sizes.h;

    //automatyczne celowanie :D
    for( Uint16 i = 0; i < 60; i++ )

        if( point.x < i * 50 )
        {
            point.x = i * 50 -50;
            break;
        }

    for( Uint16 i = 0; i < 60; i++ )
        if( point.y < i * 50 )
        {
            point.y = i * 50 -50;
            break;
        }
    bufor.x = point.x;
    bufor.y = point.y;

    SDL_RenderCopy( renderer, texture, NULL, &bufor );
}

void Map_editor::close()
{
    delete [] rect;
    SDL_DestroyTexture( texture );
}
