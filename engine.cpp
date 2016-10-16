#include "engine.h"
#include <stdio.h>

// Create objects.
Engine::Engine()
{
    core = new Core( 660, 480, -1 );
	core->setColor( 0xFF, 0xFF, 0xFF );
	sprite = new MySprite;
}


// Free objects.
void Engine::free()
{
	delete core;
	delete sprite;
}

void Engine::load()
{
	core->load( "Collision detection by pixel" );
	sprite->loadByImage( "image.png" );
	sprite->center( 0, 0, core->getWidth(), core->getHeight() );
	sprite->setAlpha( 0xFF );
}


// Control objects.
void Engine::events()
{
    while( core->getWindow()->pollEvent( core->getEvent() ) )
    {
        if( core->getEvent().type == sf::Event::Closed )
        {
            core->isOpen() = false;
        }
		
		if( core->getEvent().type == sf::Event::MouseButtonPressed )
		{
			x = core->getEvent().mouseButton.x;
			y = core->getEvent().mouseButton.y;
				
			if( sprite->checkPixelCollision( x, y ) )
			{
				printf( "\x1B[32mFound visible pixel!\x1B[0m\n" );
			}
			else
			{
				printf( "\x1B[91mNot found visible pixel!\x1B[0m\n" );
			}
		}
    }
}

// Render objects.
void Engine::states()
{
	core->getWindow()->draw( sprite->get() );
}







// We don't care about things below.
// They will look the same all time
void Engine::loop()
{
    while( core->isOpen() )
    {
        core->clear();

        events();
        states();

        core->display();
    }
}

// Delete engine equils delete objects
Engine::~Engine()
{
    free();
}
