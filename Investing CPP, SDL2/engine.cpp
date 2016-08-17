#include "engine.h"

Engine::Engine()
{
	core = new Core;
	title = new Title;
	goal = new Goal( 16, true, true, "goal: ", "0" );
	currency = new Currency;
	attain = new Attain;
	value = new Value;
}

Engine::~Engine()
{
	// empty
}

void Engine::free()
{
	delete title;
	delete goal;
	delete currency;
	delete attain;
	delete value;
	
	delete core;
}

	
bool Engine::load()
{
	core->init();
	
	if( !title->load( core->getRenderer(), core->getWidth() ) )
	{
		return false;
	}
	
	if( !goal->load( core->getRenderer(), title->getH()+5 ) )
	{
		return false;
	}
	
	if( !currency->load( core->getRenderer(), title->getH()+5, core->getWidth() ) )
	{
		return false;
	}
	
	if( !attain->load( core->getRenderer(), goal->getB()+5 ) )
	{
		return false;
	}
	
	if( !value->load( core->getRenderer(), core->getWindow(), goal->getB()+5 ) )
	{
		return false;
	}
	
	return true;
}

void Engine::handle()
{
	while( SDL_PollEvent( &core->getEvent() ) != 0 )
	{
		if( core->getEvent().type == SDL_QUIT )
		{
			core->isQuit() = true;
		}
		
		goal->handle( core->getEvent() );
		currency->handle( core->getEvent() );
		value->handle( core->getEvent(), core->getRenderer(), core->getWindow() );
	}
}

void Engine::draw()
{
	title->render( core->getRenderer(), core->getWidth(), core->getHeight() );
	goal->render( core->getRenderer(), core->getWidth() );
	currency->render( core->getRenderer() );
	attain->render( core->getRenderer(), core->getWidth() );
	value->render( core->getRenderer() );
	
	attain->setAttain( value->get(), goal->getCost(), core->getRenderer() );
}

void Engine::loop()
{
	while( !core->isQuit() )
	{
		core->top_render();
		
		handle();
		draw();
		
		core->bot_render();
	}
}
