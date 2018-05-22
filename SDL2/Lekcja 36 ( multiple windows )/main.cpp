#include <SDL.h>
#include <stdio.h>
#include <string>
#include <sstream>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Total windows
const int TOTAL_WINDOWS = 2;

class Window
{
	public:
		//Intializes internals
		Window();

		//Creates window
		bool init();

		//Handles window events
		void handleEvent( SDL_Event& e );

		//Focuses on window
		void focus();

		//Shows windows contents
		void render();

		//Deallocates internals
		void free();

		//Window dimensions
		int getWidth();
		int getHeight();

		//Window focii
		bool hasMouseFocus();
		bool hasKeyboardFocus();
		bool isMinimized();
		bool isShown();

	private:
		//Window data
		SDL_Window* window;
		SDL_Renderer* renderer;
		int windowID;

		//Window dimensions
		int width;
		int height;

		//Window focus
		bool mouseFocus;
		bool keyboardFocus;
		bool fullScreen;
		bool minimized;
		bool shown;
};

//Starts up SDL and creates window
bool init();

//Frees media and shuts down SDL
void close();

//Our custom windows
Window windows[ TOTAL_WINDOWS ];

Window::Window()
{
	//Initialize non-existant window
	window = NULL;
	renderer = NULL;

	mouseFocus = false;
	keyboardFocus = false;
	fullScreen = false;
	shown = false;
	windowID = -1;

	width = 0;
	height = 0;
}

bool Window::init()
{
	//Create window
	window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE );
	if( window != NULL )
	{
		mouseFocus = true;
		keyboardFocus = true;
		width = SCREEN_WIDTH;
		height = SCREEN_HEIGHT;

		//Create renderer for window
		renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
		if( renderer == NULL )
		{
			printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
			SDL_DestroyWindow( window );
			window = NULL;
		}
		else
		{
			//Initialize renderer color
			SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );

			//Grab window identifier
			windowID = SDL_GetWindowID( window );

			//Flag as opened
			shown = true;
		}
	}
	else
	{
		printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
	}

	return window != NULL && renderer != NULL;
}

void Window::handleEvent( SDL_Event& e )
{
	//If an event was detected for this window
	if( e.type == SDL_WINDOWEVENT && e.window.windowID == windowID )
	{
		//Caption update flag
		bool updateCaption = false;

		switch( e.window.event )
		{
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

		//Update window caption with new data
		if( updateCaption )
		{
			std::stringstream caption;
			caption << "SDL Tutorial - ID: " << windowID << " MouseFocus:" << ( ( mouseFocus ) ? "On" : "Off" ) << " KeyboardFocus:" << ( ( keyboardFocus ) ? "On" : "Off" );
			SDL_SetWindowTitle( window, caption.str().c_str() );
		}
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
		//Clear screen
		SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
		SDL_RenderClear( renderer );

		//Update screen
		SDL_RenderPresent( renderer );
	}
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


bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		if( !windows[ 0 ].init() )
		{
			printf( "Window 0 could not be created!\n" );
			success = false;
		}
	}

	return success;
}

void close()
{
	//Destroy windows
	for( int i = 0; i < TOTAL_WINDOWS; ++i )
	{
		windows[ i ].free();
	}

	//Quit SDL subsystems
	SDL_Quit();
}

int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Initialize the rest of the windows
		for( int i = 1; i < TOTAL_WINDOWS; ++i )
		{
			windows[ i ].init();
		}

		//Main loop flag
		bool quit = false;

		//Event handler
		SDL_Event e;

		//While application is running
		while( !quit )
		{
			//Handle events on queue
			while( SDL_PollEvent( &e ) != 0 )
			{
				//User requests quit
				if( e.type == SDL_QUIT )
				{
					quit = true;
				}

				//Handle window events
				for( int i = 0; i < TOTAL_WINDOWS; ++i )
				{
					windows[ i ].handleEvent( e );
				}

				//Pull up window
				if( e.type == SDL_KEYDOWN )
				{
					switch( e.key.keysym.sym )
					{
						case SDLK_1:
						windows[ 0 ].focus();
						break;

						case SDLK_2:
						windows[ 1 ].focus();
						break;

						case SDLK_3:
						windows[ 2 ].focus();
						break;
					}
				}
			}

			//Update all windows
			for( int i = 0; i < TOTAL_WINDOWS; ++i )
			{
				windows[ i ].render();
			}

			//Check all windows
			bool alWindowsClosed = true;
			for( int i = 0; i < TOTAL_WINDOWS; ++i )
			{
				if( windows[ i ].isShown() )
				{
					alWindowsClosed = false;
					break;
				}
			}

			//Application closed all windows
			if( alWindowsClosed )
			{
				quit = true;
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}
