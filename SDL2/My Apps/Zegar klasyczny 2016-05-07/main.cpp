#include "engine.h"
#include <stdio.h>
#include <windows.h>

int main( int argc, char** argv )
{
    Engine* engine;
    engine = new Engine;

    if( !engine->init() )
    {
        printf( "Nie zainicjowano programu!\n" );
        engine->close();
        SDL_Delay( 50000 );
    }
    else
    {
        printf( "PROGRAM: inicjowanie programu " );
        SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 14 );
        printf( "zakonczone sukcesem...\n" );
        SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 7 );

        engine->loop();
        engine->close();
        delete engine;
    }

    return 0;
}
