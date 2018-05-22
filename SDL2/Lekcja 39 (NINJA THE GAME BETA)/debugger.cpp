#include "debugger.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <windows.h>

/*
BLACK 0 -
BLUE 1 BLUE
GREEN 2 GREEN
CYAN 3 BLUE + GREEN
RED 4 RED
MAGENTA 5 BLUE + RED
BROWN 6 GREEN + RED
LIGHTGRAY 7 BLUE + GREEN + RED
DARKGRAY 8 INTENSITY
LIGHTBLUE 9 BLUE + INTENSITY
LIGHTGREEN 10 GREEN + INTENSITY
LIGHTCYAN 11 BLUE + GREEN + INTENSITY
LIGHTRED 12 RED + INTENSITY
LIGHTMAGENTA 13 BLUE + RED + INTENSITY
YELLOW 14 GREEN + RED + INTENSITY
WHITE 15 BLUE + GREEN + RED + INTENSITY
*/

namespace deb
{

    void setColor( uint8_t i )
    {
        SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), i );
    }

    std::string toPL( const char * text )
    {
        std::string result;

        for(; * text; text++ )

        switch( * text )
        {
            case 'π': result += static_cast < char >( 0xa5 ); break;
            case 'Ê': result += static_cast < char >( 0x86 ); break;
            case 'Í': result += static_cast < char >( 0xa9 ); break;
            case '≥': result += static_cast < char >( 0x88 ); break;
            case 'Ò': result += static_cast < char >( 0xe4 ); break;
            case 'Û': result += static_cast < char >( 0xa2 ); break;
            case 'ú': result += static_cast < char >( 0x98 ); break;
            case 'ø': result += static_cast < char >( 0xbe ); break;
            case 'ü': result += static_cast < char >( 0xab ); break;
            case '•': result += static_cast < char >( 0xa4 ); break;
            case '∆': result += static_cast < char >( 0x8f ); break;
            case ' ': result += static_cast < char >( 0xa8 ); break;
            case '£': result += static_cast < char >( 0x9d ); break;
            case '—': result += static_cast < char >( 0xe3 ); break;
            case '”': result += static_cast < char >( 0xe0 ); break;
            case 'å': result += static_cast < char >( 0x97 ); break;
            case 'Ø': result += static_cast < char >( 0xbd ); break;
            case 'è': result += static_cast < char >( 0x8d ); break;
            default: result += * text; break;
        }

        return result;
    }


    void SDL_InitError()
    {
        setColor( 15 );
        printf( "P" );
        setColor( 12 );
        printf( "L " );

        setColor( 7 );
        printf( "Nie zainicjowano biblioteki " );
        setColor( 18 );
        printf( "SDL" );
        setColor( 7 );
        printf( "!" );

        setColor( 4 );
        printf( " Error: " );
        setColor( 7 );
        printf( "%s\n", SDL_GetError() );
    }

    void IMG_InitError()
    {
        setColor( 15 );
        printf( "P" );
        setColor( 12 );
        printf( "L " );

        setColor( 7 );
        printf( "Nie zainicjowano biblioteki " );
        setColor( 19 );
        printf( "IMG" );
        setColor( 7 );
        printf( "!" );

        setColor( 4 );
        printf( " Error: " );
        setColor( 7 );
        printf( "%s\n", IMG_GetError() );
    }

    void MIX_InitError()
    {
        setColor( 15 );
        printf( "P" );
        setColor( 12 );
        printf( "L " );

        setColor( 7 );
        printf( "Nie zainicjowano biblioteki " );
        setColor( 20 );
        printf( "MIX" );
        setColor( 7 );
        printf( "!" );

        setColor( 4 );
        printf( " Error: " );
        setColor( 7 );
        printf( "%s\n", Mix_GetError() );
    }

    void TTF_InitError()
    {
        setColor( 15 );
        printf( "P" );
        setColor( 12 );
        printf( "L " );

        setColor( 7 );
        printf( "Nie zainicjowano biblioteki " );
        setColor( 21 );
        printf( "TTF" );
        setColor( 7 );
        printf( "!" );

        setColor( 4 );
        printf( " Error: " );
        setColor( 7 );
        printf( "%s\n", TTF_GetError() );
    }



    void linearFilteringError()
    {
        setColor( 15 );
        printf( "P" );
        setColor( 12 );
        printf( "L " );

        setColor( 5 );
        printf( "Ostrze%senie: ", toPL( "ø" ).c_str() );
        setColor( 7 );
        printf( "Liniowe filtrowanie tekstur jest nieaktywne!\n" );
    }

    void createWindowError()
    {
        setColor( 15 );
        printf( "P" );
        setColor( 12 );
        printf( "L " );

        setColor( 7 );
        printf( "Nie utworzono okna! " );

        setColor( 4 );
        printf( "Error: " );
        setColor( 7 );
        printf( "%s\n", SDL_GetError() );
    }

    void createRendererError()
    {
        setColor( 15 );
        printf( "P" );
        setColor( 12 );
        printf( "L " );

        setColor( 7 );
        printf( "Nie utworzono renderera! " );

        setColor( 4 );
        printf( "Error: " );
        setColor( 7 );
        printf( "%s\n", SDL_GetError() );
    }



    void loadingSurfaceError( std::string path )
    {
        setColor( 15 );
        printf( "P" );
        setColor( 12 );
        printf( "L " );

        setColor( 6 );
        printf( "%s", toPL( "Ostrzeøenie: " ).c_str() );

        setColor( 7 );
        printf( "Nie utworzono powierzchni z %s ", path.c_str() );

        setColor( 4 );
        printf( "Error: " );
        setColor( 7 );
        printf( "%s\n", SDL_GetError() );
    }

    void loadingSurfaceFromTextError()
    {
        setColor( 15 );
        printf( "P" );
        setColor( 12 );
        printf( "L " );

        setColor( 6 );
        printf( "Ostrze%senie: ", toPL( "ø" ).c_str() );

        setColor( 7 );
        printf( "Nie utworzono powierzchni z tekstu " );

        setColor( 4 );
        printf( "Error: " );
        setColor( 7 );
        printf( "%s\n", TTF_GetError() );
    }

    void createTextureFromSurfaceError( std::string path )
    {
        setColor( 15 );
        printf( "P" );
        setColor( 12 );
        printf( "L " );

        setColor( 6 );
        printf( "Ostrze%senie: ", toPL( "ø" ).c_str() );

        setColor( 7 );
        printf( "Nie utworzono tekstury z %s ", path.c_str() );

        setColor( 4 );
        printf( "Error: " );
        setColor( 7 );
        printf( "%s\n", SDL_GetError() );
    }

    void setTextureError()
    {
        setColor( 15 );
        printf( "P" );
        setColor( 12 );
        printf( "L " );

        setColor( 5 );
        printf( "Ostrze%senie: ", toPL( "ø" ).c_str() );
        setColor( 7 );
        printf( "Nie ustawiono tekstury!\n" );
    }


    void loadingMusicError( std::string path )
    {
        setColor( 15 );
        printf( "P" );
        setColor( 12 );
        printf( "L " );

        setColor( 6 );
        printf( "Ostrze%senie: ", toPL( "ø" ).c_str() );

        setColor( 7 );
        printf( "Nie wczytano muzyki %s ", path.c_str() );

        setColor( 4 );
        printf( "Error: " );
        setColor( 7 );
        printf( "%s\n", Mix_GetError() );
    }

    void loadingChunkError(  std::string path )
    {
        setColor( 15 );
        printf( "P" );
        setColor( 12 );
        printf( "L " );

        setColor( 6 );
        printf( "Ostrze%senie: ", toPL( "ø" ).c_str() );

        setColor( 7 );
        printf( "Nie wczytano d%swi%sku %s ", toPL( "ü" ).c_str(), toPL( "Í" ).c_str(), path.c_str() );

        setColor( 4 );
        printf( "Error: " );
        setColor( 7 );
        printf( "%s\n", Mix_GetError() );
    }

    void loadingFontError(  std::string path )
    {
        setColor( 15 );
        printf( "P" );
        setColor( 12 );
        printf( "L " );

        setColor( 6 );
        printf( "Ostrze%senie: ", toPL( "ø" ).c_str() );

        setColor( 7 );
        printf( "Nie wczytano czcionki %s ", path.c_str() );

        setColor( 4 );
        printf( "Error: " );
        setColor( 7 );
        printf( "%s\n", TTF_GetError() );
    }

    void loadingFileError( std::string path )
    {
        setColor( 15 );
        printf( "P" );
        setColor( 12 );
        printf( "L " );

        setColor( 6 );
        printf( "Ostrze%senie (plik txt): ", toPL( "ø" ).c_str() );

        setColor( 7 );
        perror( "" );
    }

}


