#include "control.h"

Control::Control()
{
    state = 0;
    mouse.x = 0;
    mouse.y = 0;
    counter = 1;
    ball_speed = 0;
}

bool Control::load()
{
    SDL_Texture* temporary = loadTexture( "images/deska1.png", board_one );
    board_two = board_one;

    if( temporary == NULL )
    {
        printf( "Nie ustawiono wymiarow obiektu deska.png!\n" );
        return false;
    }
    else
    {
        board_one.y = SCREEN_HEIGHT - board_one.h - 10;
        board_two.y = SCREEN_HEIGHT - board_two.h - 10;

        board_one.x = SCREEN_WIDTH / 4 - board_one.w / 2;
        board_two.x = SCREEN_WIDTH / 4 * 3 - board_two.w / 2;
    }

    temporary = loadTexture( "images/pilka.png", ball );
    if( temporary == NULL )
    {
        printf( "Nie ustawiono wymiarow obiektu pilka.png!\n" );
        return false;
    }
    else
    {
        ball.y = SCREEN_HEIGHT / 2 - ball.h / 2;
        ball.x = SCREEN_WIDTH / 4 - ball.w / 2;
    }

    temporary = loadTexture( "images/play.png", play );
    if( temporary == NULL )
    {
        printf( "Nie ustawiono wymiarow obiektu play.png!\n" );
        return false;
    }
    else
    {
        play.y = SCREEN_HEIGHT / 3 - play.h / 2;
        play.x = SCREEN_WIDTH / 2 - play.w / 2;
    }

    temporary = loadTexture( "images/exit.png", exit );
    if( temporary == NULL )
    {
        printf( "Nie ustawiono wymiarow obiektu exit.png!\n" );
        return false;
    }
    else
    {
        exit.y = SCREEN_HEIGHT / 3 * 2 - exit.h / 2;
        exit.x = SCREEN_WIDTH / 2 - exit.w / 2;
    }

    temporary = loadTexture( "images/reset.png", reset );
    if( temporary == NULL )
    {
        printf( "Nie ustawiono wymiarow obiektu reset.png!\n" );
        return false;
    }
    else
    {
        reset.y = SCREEN_HEIGHT / 3 - reset.h / 2;
        reset.x = SCREEN_WIDTH / 2 - reset.w / 2;
    }

    temporary = loadTexture( "images/menu.png", menu );
    if( temporary == NULL )
    {
        printf( "Nie ustawiono wymiarow obiektu menu.png!\n" );
        return false;
    }
    else
    {
        menu.y = SCREEN_HEIGHT / 3 * 2 - menu.h / 2;
        menu.x = SCREEN_WIDTH / 2 - menu.w / 2;
    }

    SDL_DestroyTexture( temporary );
    temporary = NULL;

    return true;
}

void Control::mouse_control()
{
    SDL_Event e;
    while( SDL_PollEvent( &e ) != 0 )
    {
        if( e.type == SDL_QUIT )
            SDL_Quit();

        if( e.type == SDL_MOUSEBUTTONDOWN )
        {
            int x, y;
            SDL_GetMouseState( &x, &y );
            if( FRAME == 0 )
            {
                if( x > play.x && x < play.x + play.w && y > play.y && y < play.y + play.h )
                    FRAME = 1;

                else if( x > exit.x && x < exit.x + exit.w && y > exit.y && y < exit.y + exit.h )
                    SDL_Quit();
            }

            if( FRAME == 2 )
            {
                if( x > reset.x && x < reset.x + reset.w && y > reset.y && y < reset.y + reset.h )
                    FRAME = 1;

                else if( x > menu.x && x < menu.x + menu.w && y > menu.y && y < menu.y + menu.h )
                    FRAME = 0;
            }

            if( FRAME == 1 )
            {
                if( x > ball.x && x < ball.x + ball.w && y > ball.y && y < ball.y + ball.h )
                {
                    if( counter == 0 )
                    {
                        counter = 1;
                    }
                    else
                        counter = 0;

                    state = 1;
                    ball_speed = 1;
                }
            }
        }
    }
}

void Control::keys_control()
{
    const Uint8* key = SDL_GetKeyboardState( NULL );

    int speed = 3;

    if( key[ SDL_SCANCODE_S ] )
        speed = 5;

    if( key[ SDL_SCANCODE_A ] && board_one.x > 0 )
        board_one.x -= speed;

    if( key[ SDL_SCANCODE_D ] && board_one.x + board_one.w < SCREEN_WIDTH / 2 )
        board_one.x += speed;

    speed = 3;

    if( key[ SDL_SCANCODE_DOWN ] )
        speed = 5;

    if( key[ SDL_SCANCODE_LEFT ] && board_two.x > SCREEN_WIDTH / 2 )
        board_two.x -= speed;

    if( key[ SDL_SCANCODE_RIGHT ] && board_two.x + board_two.w < SCREEN_WIDTH )
        board_two.x += speed;
}

void Control::ball_control()
{
    if( state == 0 )
    {
        if( counter == 0 )
        {
            ball.y = SCREEN_HEIGHT / 2 - ball.h;
            ball.x = SCREEN_WIDTH / 4 - ball.w;
        }
        else
        {
            ball.y = SCREEN_HEIGHT / 2 - ball.h;
            ball.x = SCREEN_WIDTH / 4 * 3 - ball.w;
        }
    }
    ball_speed += 0.000001;
    if( state == 1 )
    {
        ball.y -= ball_speed;
        ball.x += ball_speed;
    }

    if( state == 2 )
    {
        ball.y += ball_speed;
        ball.x += ball_speed;
    }

    if( state == 3 )
    {
        ball.y -= ball_speed;
        ball.x -= ball_speed;
    }

    if( state == 4 )
    {
        ball.y += ball_speed;
        ball.x -= ball_speed;
    }
    cout<<ball_speed<<endl;
}

void Control::collision()
{

    if( ball.x + ball.w > board_one.x && ball.x < board_one.x + board_one.w && ball.y + ball.h > board_one.y && ball.y < board_one.y + board_one.h )
    {
        if( state == 2 )
            state = 1;
        else
            state = 3;
    }

    if( ball.x + ball.w > board_two.x && ball.x < board_two.x + board_two.w && ball.y + ball.h > board_two.y && ball.y < board_two.y + board_two.h )
    {
        if( state == 2 )
            state = 1;
        else
            state = 3;
    }

    if( ball.x < 0 )
    {
        if( state == 3 )
            state = 1;
        else
            state = 2;
    }

    if( ball.x >= SCREEN_WIDTH / 2 )
    {
        if( ball.x - 5 < SCREEN_WIDTH / 2 )
        {
            if( state == 3 )
                state = 2;
            else
                state = 2;
        }
    }

    if( ball.x <= SCREEN_WIDTH / 2 )
    {
        if( ball.x + 5 > SCREEN_WIDTH / 2 - 3 )
        {
            if( state == 1 )
                state = 4;
            else
                state = 4;
        }
    }

    if( ball.x > SCREEN_WIDTH )
    {
        if( state == 1 )
            state = 3;
        else
            state = 4;
    }

    if( ball.y > SCREEN_HEIGHT )
    {
        state = 0;
        FRAME = 2;
    }

    if( ball.y < 0 )
    {
        if( ball.x < SCREEN_WIDTH / 2 )
            ball.x = ( SCREEN_WIDTH / 2 ) + ( SCREEN_WIDTH / 2 - ball.x );

        else
            ball.x = ( SCREEN_WIDTH / 2 ) - ( ball.x - SCREEN_WIDTH / 2 );

        if( state == 1 )
            state = 4;
        else
            state = 2;
    }
}
