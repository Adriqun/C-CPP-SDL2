#include "engine.h"
#include "timer.h"
#include <stdio.h>
#include <SDL_image.h>

Engine::Engine()
{
    window = NULL;
    renderer = NULL;

    core = new Core( 1024, 768 );
    loading = new Loading;
    intro = new Intro;

    menu = new Menu;
    scores = new Scores;
    options = new Options;

    storm = new Storm;
    wall = new Wall;

    hero = new Hero;
    shuriken = new Shuriken;

    defeat = new Defeat;
    hearts = new Hearts;
    pause = new Pause;
    points = new Points;

    enemy = new Enemy;
}

bool Engine::load()
{
    static int counter = 0;     /* We started from object 0 */
    static const int max = 20; /* Max amount of objects */

    switch( counter )
    {

    case 0:
        if( !loading->load( renderer, window ) )
        {
            printf( "Error at load object loading!\n" );
        }
        break;


    case 1:
        if( !intro->load( renderer, window ) )
        {
            printf( "Error at load object intro!\n" );
        }
        break;


    case 2:
        if( !menu->load( renderer, window ) )
        {
            printf( "Error at load object menu!\n" );
        }
        break;


    case 3:
        if( !scores->load( renderer, window ) )
        {
            printf( "Error at load object scores!\n" );
        }
        break;


    case 5:
        if( !storm->load( renderer, window ) )
        {
            printf( "Error at load object storm!\n" );
        }
        break;


    case 6:
        if( !wall->load( renderer, window ) )
        {
            printf( "Error at load object wall!\n" );
        }
        break;


    case 7:
        if( !hero->load( renderer, window ) )
        {
            printf( "Error at load object hero!\n" );
        }
        break;


    case 8:
        if( !shuriken->load( renderer, window ) )
        {
            printf( "Error at load object shuriken!\n" );
        }
        break;


    case 9:
        if( !defeat->load( renderer, window ) )
        {
            printf( "Error at load object defeat!\n" );
        }
        break;


    case 10:
        if( !hearts->load( renderer, window ) )
        {
            printf( "Error at load object hearts!\n" );
        }
        break;


    case 11:
        if( !pause->load( renderer, window ) )
        {
            printf( "Error at load object pause!\n" );
        }
        break;


    case 12:
        if( !points->load( renderer, window ) )
        {
            printf( "Error at load object points!\n" );
        }
        break;


    case 13:
        if( !options->load( renderer, window ) )
        {
            printf( "Error at load object options!\n" );
        }
        break;


    case 14:
        if( !enemy->load() )
        {
            printf( "Error at load object enemy!\n" );
        }
        break;

    }

    counter ++;

    if( counter != max )
    {
        loading->render( renderer, max-1 );
    }
    else
    {
        return true;
    }

    return false;
}

void Engine::handle()
{
    while( SDL_PollEvent( &event ) != 0 )
    {
        if( event.type == SDL_QUIT )
        {
            core->setQuit();
        }
    }
}

void Engine::render()
{
    if( core->getFrame() == -1 )
    {
        if( load() )
        {
            delete loading;
            loading = NULL;
            core->setFrame( 0 );
        }
    }

    if( core->getFrame() == -2 )
    {
        wall->renderLive( renderer );
        wall->addBlock( renderer, event );
    }

    if( core->getFrame() == 0 )
    {
        intro->render( renderer, core->getFPS() + 10 );

        if( intro->isClose() )
        {
            delete intro;
            intro = NULL;
            core->setFrame( 1 );
        }
    }

    if( core->getFrame() == 1 )
    {
        if( menu->getState() < 0 )
        {
            scores->fadeIO( -10 );
            options->fadeIO( -10 );
            menu->fadeIO( 2 );
        }

        menu->control();
        menu->render( renderer );
        menu->play();


        // We start a game
        if( menu->getState() == 0 )
        {
            Mix_FadeOutMusic( 1000 );
            core->setFrame( 2 );
        }

        // We click scores
        else if( menu->getState() == 1 )
        {
            scores->fadeIO( 2 );
            scores->render( renderer );
        }

        // We click options
        else if( menu->getState() == 2 )
        {
            options->fadeIO( 2 );
            options->render( renderer );
        }

        // We click exit
        else if( menu->getState() == 3 )
        {
            core->setQuit();
        }
    }

    if( core->getFrame() == 2 )
    {
        wall->play();
        pause->control();

        bool run = false;

        if( pause->getState() == 0 )
        {
            points->fadeIn();
            pause->fadeIn();
            hearts->fadeIn();
            hero->fadeIn();
            shuriken->fadeIn();
            wall->fadeIn();
            enemy->mechanics( renderer, window );
        }


        hearts->set( hero->getX(), hero->getY() );
        if( pause->getState() == 0 )
        {
            hero->idle();
            run = hero->run();
        }


        wall->render( renderer, run );
        enemy->faster( run );
        enemy->render( renderer );

        points->render( renderer, run );

        if( pause->getState() == 1 )    wall->pause();

        if( pause->getState() == 0 )
        {
            hearts->lose( enemy->checkCollision( hero->getRect() ) );
            bool hit = enemy->checkCollision( shuriken->getRect() );
            shuriken->setState( hit );
            points->add( hit );
            hero->render10( renderer, hit );
            hero->setDead( hearts->dead() );
            hero->backX( wall->checkCollision( hero->getRect() ) );

            hero->gravitation();
            hero->backY( wall->checkCollision( hero->getRect() ) );

            hero->jump();
            hero->attack( shuriken->control( hero->getX(), hero->getY(), core->getWidth() ) );
            storm->random( renderer, core->getWidth(), core->getHeight() );
        }

        pause->render( renderer );
        storm->render( renderer );
        shuriken->render( renderer );
        hero->render( renderer );
        hearts->render( renderer );

        if( hero->getDead( core->getHeight() ) )
        {
            points->sumUp();
            Mix_FadeOutMusic( 1000 );
            core->setFrame( 3 );
        }
    }


    if( core->getFrame() == 3 )
    {
        storm->halt();
        points->fadeOut();
        hero->fadeOut();
        hearts->fadeOut();
        shuriken->fadeOut();
        wall->fadeOut();
        pause->fadeOut();

        wall->renderLive( renderer );
        points->render( renderer, false );
        storm->fadeOut( renderer );
        shuriken->render( renderer );
        hero->render( renderer );
        hearts->render( renderer );
        defeat->render( renderer );
        pause->render( renderer );

        if( defeat->control() == 0 )
        {
            core->setFrame( 1 );
            menu->load( renderer, window );
            wall->load( renderer, window );
            storm->load( renderer, window );
            hero->load( renderer, window );
            defeat->load( renderer, window );
            hearts->load( renderer, window );
            pause->load( renderer, window );
            scores->load( renderer, window );
            points->load( renderer, window );
            delete enemy;
            enemy = new Enemy;
        }
        else if( defeat->control() == 1 )
        {
            core->setFrame( 2 );
            wall->load( renderer, window );
            storm->load( renderer, window );
            hero->load( renderer, window );
            defeat->load( renderer, window );
            hearts->load( renderer, window );
            pause->load( renderer, window );
            points->load( renderer, window );
            delete enemy;
            enemy = new Enemy;
        }
    }
}

void Engine::free()
{
    delete core;

    if( intro != NULL )
        delete intro;

    delete menu;
    delete scores;
    delete options;

    delete storm;
    delete wall;

    delete hero;
    delete shuriken;

    delete defeat;
    delete hearts;
    delete points;
    delete pause;
}

bool Engine::init()
{
    register bool success = true;

    if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
    {
        printf( "SDL could not initialize! Error %s\n", SDL_GetError() );
        success = false;
    }

    else if( !( IMG_Init( IMG_INIT_PNG )&IMG_INIT_PNG ) )
    {
        printf( "IMG could not initialize! Error %s\n", IMG_GetError() );
        success = false;
    }

    else if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        printf( "Mix could not initialize! Error: %s\n", Mix_GetError() );
        success = false;
    }

    else if( TTF_Init() < 0 )
    {
        printf( "TTF could not initialize! Error: %s\n", TTF_GetError() );
        success = false;
    }
    else
    {
        if( !core->createWindow( window, SDL_WINDOW_SHOWN ) )
        {
            success = false;
        }
        else
        {
            register const char* icon = "window/icon.bmp";
            if( !core->setWindowIcon( window, icon ) )
            {
                success = false;
            }
        }

        if( !core->createRenderer( window, renderer, SDL_RENDERER_ACCELERATED ) )
        {
            success = false;
        }
    }

    return success;
}

void Engine::loop()
{
    Timer timer( core->getFPS() );

    while( !core->getQuit() )
    {
        timer.start();
        core->topRender( renderer );

        handle();
        render();

        core->botRender( renderer );
        timer.finish();
    }
}

void Engine::close()
{
    free();

    SDL_DestroyWindow( window );
    window = NULL;

    SDL_DestroyRenderer( renderer );
    renderer = NULL;

    SDL_Quit();
    IMG_Quit();
    Mix_Quit();
    TTF_Quit();
}
