#include "keyboard.h"

Keyboard::Keyboard()
{
    floor.x = 0;
    floor.y = 0;
    vel = 0;

    point.x = 0;
    point.y = 0;
    click = 0;

    ball.x = 0;
    ball.y = 0;
    state = 3;
    velBall = 0;

    key = SDL_GetKeyboardState( NULL );
    defeat = 0;
}

Keyboard::~Keyboard()
{
    key = SDL_GetKeyboardState( NULL );
}

bool Keyboard::load()
{
    SDL_Surface* surface = IMG_Load( "deska.png" );
    if( surface == NULL )
    {
        printf( "Nie ustawiono wymiarow deski! (keyboard)\n" );
        return false;
    }
    else
    {
        floor.w = surface -> w;
        floor.h = surface -> h;

        floor.x = ( SCREEN_WIDTH / 2 ) - ( floor.w / 2 );
        floor.y = SCREEN_HEIGHT - ( floor.h + 10 );

        vel = 5;
    }

    surface = IMG_Load( "pilka.png" );
    if( surface == NULL )
    {
        printf( "Nie ustawiono wspolrzednych pilki (keyboard)! \n" );
        return false;
    }
    else
    {
        ball.w = surface -> w;
        ball.h = surface -> h;

        ball.x = floor.x + ( floor.w / 2 ) - ( ball.w / 2 ) ;
        ball.y = floor.y - ( floor.h / 2 ) - ball.h;

        velBall = 4;
    }
    SDL_FreeSurface( surface );

    return true;
}

void Keyboard::keys()
{
    vel = 5;
    int height, width;
    SDL_GetWindowSize( window, &width, &height );

    if( key[ SDL_SCANCODE_S ] )                                 vel = 10;

    if( key[ SDL_SCANCODE_D ] && floor.x + floor.w < width )    floor.x += vel;

    if( key[ SDL_SCANCODE_A ] && floor.x > 0 )                  floor.x -= vel;

    floor.y =  height - ( floor.h + 10 );
}

void Keyboard::mouse()
{
    while( SDL_PollEvent( &e ) != 0 )
    {
        if( e.type == SDL_QUIT )
            SDL_Quit();
        if( e.type == SDL_MOUSEMOTION )
        {
           SDL_GetMouseState( &point.x, &point.y );
           click = 0;
        }

        if( e.type == SDL_MOUSEBUTTONDOWN ) click = 1;
    }
}

void Keyboard::collision()
{
    int height, width;
    SDL_GetWindowSize( window, &width, &height );

    //gdy pilka napotka deske
    if( ball.x < ( floor.x + ( floor.w / 3 * 2 ) ) && ( ball.x + ( ball.w / 2 ) ) > ( floor.x + ( floor.w / 3 ) ) && ball.y < floor.y + floor.h && ball.y + ball.h > floor.y )
    {
        if( state == 2 )
            state = 1;
        else
            state = 3;
        velBall = 4;
    }
    else if( ball.x < ( floor.x + ( floor.w / 3 ) ) && ( ball.x + ( ball.w / 2 ) ) > floor.x && ball.y < floor.y + floor.h && ball.y + ball.h > floor.y )
    {
        if( state == 2 )
            state = 1;
        else
            state = 3;
        velBall = 8;
    }
    else if( ball.x < floor.x + floor.w && ( ball.x + ( ball.w / 2 ) ) > ( floor.x + ( floor.w / 3 * 2 ) ) && ball.y < floor.y + floor.h && ball.y + ball.h > floor.y )
    {
        if( state == 2 )
            state = 1;
        else
            state = 3;
        velBall = 8;
    }


    // gdy pilka napotka jakas sciane
    else if( ball.x < 0 )
    {
        if( state == 4 )
            state = 2;
        else
            state = 1;
    }
    else if( ball.x + ball.w > width )
    {
        if( state == 2 )
            state = 4;
        else
            state = 3;
    }
    else if( ball.y < 0 )
    {
        if( state == 1 )
            state = 2;
        else
            state = 4;
    }
    else if( ball.y + ball.h > height ) defeat = 1;


    //lot pilki
    if( state == 1 || state == 3 )  ball.y -= velBall / 2;

    else    ball.y += velBall / 2;

    if( state == 3 || state == 4 )  ball.x -= velBall;

    else    ball.x += velBall;

    if( velBall == 4 )
        SDL_Delay(4);
    else
        SDL_Delay(7);
}
