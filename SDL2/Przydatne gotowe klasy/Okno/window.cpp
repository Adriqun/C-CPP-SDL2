#include "window.h"
#include <stdio.h>
#include <sstream>

Window::Window( int w, int h )
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

    width = w;
    height = h;
}

void Window::free()
{
    if( window != NULL )
    {
        SDL_DestroyWindow( window );
    }

    mouseFocus = false;
    keyboardFocus = false;
    width = 0;
    height = 0;
}



bool Window::init( std::string path, int x, int y, Uint32 windowFlags, Uint32 rendererFlags )
{
    window = SDL_CreateWindow( path.c_str(), x, y, width, height, windowFlags );
    if( window != NULL )
    {
        mouseFocus = true;
        keyboardFocus = true;

        renderer = SDL_CreateRenderer( window, -1, rendererFlags );
        if( renderer == NULL )
        {
            printf( "Nie utworzono renderera! Error: %s\n", SDL_GetError() );
            SDL_DestroyWindow( window );
            window = NULL;
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
        printf( "Nie utworzono okna! Error: %s\n", SDL_GetError() );
    }

    return window != NULL && renderer != NULL;
}

void Window::handleEvent( SDL_Event& e )
{
    bool updateCaption = false;

    if( e.type == SDL_WINDOWEVENT && e.window.windowID == windowID )
    {
        switch( e.window.event )
        {
        //Window moved
        case SDL_WINDOWEVENT_MOVED:
            displayID = SDL_GetWindowDisplayIndex( window );
            updateCaption = true;
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
            updateCaption = true;
            break;

        //Mouse exit
        case SDL_WINDOWEVENT_LEAVE:
            mouseFocus = false;
            updateCaption = true;
            break;

        //Keyboard focus gained
        case SDL_WINDOWEVENT_FOCUS_GAINED:
            keyboardFocus = true;
            updateCaption = true;
            break;

        //Keyboard focus lost
        case SDL_WINDOWEVENT_FOCUS_LOST:
            keyboardFocus = false;
            updateCaption = true;
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

    if( updateCaption )
    {
        std::stringstream caption;
        caption << "SDL Tutorial - ID: " << windowID << " Display: " << displayID << " MouseFocus:" << ( ( mouseFocus ) ? "On" : "Off" ) << " KeyboardFocus:" << ( ( keyboardFocus ) ? "On" : "Off" );
        SDL_SetWindowTitle( window, caption.str().c_str() );
    }
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

void Window::render()
{
    if( !minimized )
    {
        SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( renderer );

        SDL_RenderPresent( renderer );
    }
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
