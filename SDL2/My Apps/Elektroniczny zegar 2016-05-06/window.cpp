#include "window.h"
#include <windows.h>
#include <stdio.h>
#include <fstream>
#include <ctype.h>
// #include <sstream>

Window::Window()
{
    window = NULL;
    renderer = NULL;

    mouseFocus = false;
    keyboardFocus = false;
    fullScreen = false;
    minimized = false;
    shown = false;

    windowID = 0;
    displayID = -1;

    width = 0;
    height = 0;
}

Window::~Window()
{
    free();
}

void Window::free()
{
    if( window != NULL )
    {
        SDL_DestroyWindow( window );
        window = NULL;
    }

    if( renderer != NULL )
    {
        SDL_DestroyRenderer( renderer );
        renderer = NULL;
    }

    mouseFocus = false;
    keyboardFocus = false;

    width = 0;
    height = 0;
}




int Window::stringToInt( std::string &path )
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

bool Window::setDimensions( int &x, int &y )
{
    bool success = true;

    std::ifstream file;
    std::string name = "window/dimensions.txt";

    file.open( name.c_str(), std::ios::in );
    if( file.good() )
    {
        std::string line;
        int lineCounter = 0;

        while( std::getline( file, line ) )
        {
            lineCounter ++;
        }
        if( lineCounter > 4 )
        {
            printf( "\nW pliku %s znajduje sie zbyt duza ilosc wierszy (%d),\n", name.c_str(), lineCounter );
            SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 12 );
            printf( "ich liczba powinna wynosic 4!\n\n" );
            SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 7 );
            success = false;
        }
        else
        {
            bool good = true;
            file.close();
            file.open( name.c_str(), std::ios::in );

            while( std::getline( file, line ) )
            {
                int len = line.length();
                for( int i = 0; i < len; ++ i )
                {
                    if( !isdigit( line[ i ] ) )
                    {
                        printf( "\nW pliku %s, w wierszu %d wprowadzono litere %c,\n", name.c_str(), i, line[ i ] );
                        SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 12 );
                        printf( "liczba nie moze zawierac liter!\n\n" );
                        SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 7 );
                        good = false;
                    }
                }
            }

            if( good )
            {
                file.close();
                file.open( name.c_str(), std::ios::in );

                RECT rect;
                GetWindowRect( GetDesktopWindow(), &rect );
                int w = rect.right - rect.left;
                int h = rect.bottom - rect.top;

                std::getline( file, line );
                if( stringToInt( line ) > w || stringToInt( line ) < 0 )
                {
                    printf( "Niedozwolona szerokosc okna!\n" );
                    SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 12 );
                    printf( "Zaakceptowana zostanie szerokosc >= 0 oraz < %d\n", w );
                    SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 7 );
                    good = false;
                }
                else
                {
                    std::getline( file, line );
                    if( stringToInt( line ) > h || stringToInt( line ) < 0 )
                    {
                        printf( "Niedozwolona wysokosc okna!\n" );
                        SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 12 );
                        printf( "Zaakceptowana zostanie wysokosc >= 0 oraz < %d\n", h );
                        SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 7 );
                        good = false;
                    }
                    else
                    {
                        std::getline( file, line );
                        if( stringToInt( line ) > w - width || stringToInt( line ) < 0 )
                        {
                            printf( "Niedozwolona pozycja x okna!\n" );
                            SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 12 );
                            printf( "Zaakceptowana zostanie pozycja x >= 0 oraz < %d\n", w - width );
                            SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 7 );
                            good = false;
                        }
                        else
                        {
                            std::getline( file, line );
                            if( stringToInt( line ) > h - height || stringToInt( line ) < 0 )
                            {
                                printf( "Niedozwolona pozycja y okna!\n" );
                                SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 12 );
                                printf( "Zaakceptowana zostanie pozycja y >= 0 oraz < %d\n", h - height );
                                SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 7 );
                                good = false;
                            }
                        }
                    }
                }

                if( good )
                {
                    file.close();
                    file.open( name.c_str(), std::ios::in );

                    std::getline( file, line );
                    if( stringToInt( line ) == 0 )  width = 800;
                    else                            width = stringToInt( line );

                    std::getline( file, line );
                    if( stringToInt( line ) == 0 )  height = 600;
                    else                            height = stringToInt( line );

                    std::getline( file, line );
                    if( stringToInt( line ) == 0 )  x = SDL_WINDOWPOS_UNDEFINED;
                    else                            x = stringToInt( line );

                    std::getline( file, line );
                    if( stringToInt( line ) == 0 )  y = SDL_WINDOWPOS_UNDEFINED;
                    else                            y = stringToInt( line );
                }
                else
                {
                    success = false;
                }
            }
        }
    }
    else
    {
        printf( "Nie znaleziono pliku window/dimensions.txt!\n" );
        success = false;
    }

    file.close();

    return success;
}

bool Window::createWindow( std::string icon, std::string path, Uint32 flags )
{
    bool success = true;

    int x, y;
    if( setDimensions( x, y ) )
    {
        window = SDL_CreateWindow( path.c_str(), x, y, width, height, flags );
    }
    else
    {
        success = false;
    }

    if( window == NULL )
    {
        SDL_Log( "Nie utworzono okna! " );
        success = false;
    }
    else
    {
        mouseFocus = true;
        keyboardFocus = true;

        SDL_Surface* surface = SDL_LoadBMP( icon.c_str() );
        if( surface == NULL )
        {
            SDL_Log( "Nie wczytano ikony! " );
            success = false;
        }
        else
        {
            SDL_SetColorKey( surface, SDL_TRUE, SDL_MapRGB( surface->format, 0, 0xFF, 0 ) );
            SDL_SetWindowIcon( window, surface );
        }

        SDL_FreeSurface( surface );
        surface = NULL;
    }

    if( success )
    {
        printf( "WINDOW: Tworzenie okna... ");
        SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 14 );
        printf( "zakonczone sukcesem\n" );
        SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 7 );
    }

    return success;
}

bool Window::createRenderer( int index, Uint32 flags )
{
    bool success = true;

    if( window != NULL )
    {
        renderer = SDL_CreateRenderer( window, -1, flags );
        if( renderer == NULL )
        {
            SDL_DestroyWindow( window );
            window = NULL;

            SDL_Log( "Nie utworzono renderera! " );
            success = false;
        }
        else
        {
            SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );

            windowID = SDL_GetWindowID( window );
            displayID = SDL_GetWindowDisplayIndex( window );
            shown = true;
        }
    }
    else
    {
        SDL_Log( "Brak okna!" );
        success = false;
    }

    if( success )
    {
        printf( "RENDERER: Tworzenie renderera... ");
        SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 10 );
        printf( "zakonczono pomyslnie\n" );
        SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 7 );
    }

    return success;
}

void Window::handle( SDL_Event& e )
{
    // bool updateCaption = false;

    if( e.type == SDL_WINDOWEVENT && e.window.windowID == windowID )
    {
        switch( e.window.event )
        {
        //Window moved
        case SDL_WINDOWEVENT_MOVED:
            displayID = SDL_GetWindowDisplayIndex( window );
            // updateCaption = true;
            break;

        //Window appeared
        case SDL_WINDOWEVENT_SHOWN:
            shown = true;
            break;

        //Window disappeared
        case SDL_WINDOWEVENT_HIDDEN:
            shown = false;
            break;

        //Get new dimensions and repaint
        case SDL_WINDOWEVENT_SIZE_CHANGED:
            width = e.window.data1;
            height = e.window.data2;
            SDL_RenderPresent( renderer );
            break;

        //Repaint on expose
        case SDL_WINDOWEVENT_EXPOSED:
            SDL_RenderPresent( renderer );
            break;

        //Mouse enter
        case SDL_WINDOWEVENT_ENTER:
            mouseFocus = true;
            // updateCaption = true;
            break;

        //Mouse exit
        case SDL_WINDOWEVENT_LEAVE:
            mouseFocus = false;
            // updateCaption = true;
            break;

        //Keyboard focus gained
        case SDL_WINDOWEVENT_FOCUS_GAINED:
            keyboardFocus = true;
            // updateCaption = true;
            break;

        //Keyboard focus lost
        case SDL_WINDOWEVENT_FOCUS_LOST:
            keyboardFocus = false;
            // updateCaption = true;
            break;

        //Window minimized
        case SDL_WINDOWEVENT_MINIMIZED:
            minimized = true;
            break;

        //Window maxized
        case SDL_WINDOWEVENT_MAXIMIZED:
            minimized = false;
            break;

        //Window restored
        case SDL_WINDOWEVENT_RESTORED:
            minimized = false;
            break;

        //Hide on close
        case SDL_WINDOWEVENT_CLOSE:
            SDL_HideWindow( window );
            break;
        }
    }

    /*
    if( updateCaption )
    {
        std::stringstream caption;
        caption << "SDL Tutorial - ID: " << windowID << " Display: " << displayID << " MouseFocus:" << ( ( mouseFocus ) ? "On" : "Off" ) << " KeyboardFocus:" << ( ( keyboardFocus ) ? "On" : "Off" );
        SDL_SetWindowTitle( window, caption.str().c_str() );
    }
    */
}

void Window::focus()
{
    //Restore window if needed
    if( !shown )
    {
        SDL_ShowWindow( window );
    }

    //Move window forward
    SDL_RaiseWindow( window );
}




void Window::start()
{
    if( !minimized )
    {
        SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( renderer );
    }
}

void Window::present()
{
    if( !minimized )
    {
        SDL_RenderPresent( renderer );
    }
}

SDL_Window* Window::getWindow()
{
    return window;
}

SDL_Renderer* Window::getRenderer()
{
    return renderer;
}


int Window::getWidth()
{
    return width;
}

int Window::getHeight()
{
    return height;
}

bool Window::hasMouseFocus()
{
    return mouseFocus;
}

bool Window::hasKeyboardFocus()
{
    return keyboardFocus;
}

bool Window::isMinimized()
{
    return minimized;
}

bool Window::isShown()
{
    return shown;
}
