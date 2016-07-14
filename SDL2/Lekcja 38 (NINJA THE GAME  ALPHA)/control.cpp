#include "control.h"

Control::Control()
{
    screen_width = 1020;
    screen_height = 720;
}

void Control::close()
{
    delete &keyboard;
    delete &ninjaC;
    delete &shurikenC;
    delete &backgroundC;
    delete &chartC;
}


SDL_Point Control::get_background_point()
{
    if( backgroundC.point.x == 1020 )
        backgroundC.point.x = 0;

    return backgroundC.point;
}

void Control::ninja_mouse_control()
{
    while( SDL_PollEvent( &mouse.event ) != 0 )
    {

    }
}

void Control::ninja_keyboard_control()
{
    if( shurikenC.counter == 0 )
    {
        if( shurikenC.value > 1 )
                shurikenC.rect.x = ninjaC.rect.x - 22;
            else
                shurikenC.rect.x = ninjaC.rect.x + 67;
        shurikenC.rect.y = ninjaC.rect.y + 25;

        if( shurikenC.value == 3 )
            shurikenC.value = 2;

        else if( shurikenC.value == 1 )
            shurikenC.value = 0;

    }
    else if( shurikenC.counter > 0 && shurikenC.counter < 150 )
    {
        shurikenC.counter += 2;

        if( shurikenC.value > 1 )
        {
            shurikenC.rect.x += shurikenC.speed;
            shurikenC.value = 3;
        }
        else
        {
            shurikenC.rect.x -= shurikenC.speed;
            shurikenC.value = 1;
        }

    }
    else
        shurikenC.counter = 0;

    if( keyboard.key[ SDL_SCANCODE_SPACE ] )
    {
        if( shurikenC.counter == 0 )
        {
            if( shurikenC.value > 1 )
                shurikenC.rect.x = ninjaC.rect.x - 22;
            else
                shurikenC.rect.x = ninjaC.rect.x + 67;
            shurikenC.rect.y = ninjaC.rect.y + 25;

            shurikenC.counter = 1;
        }
    }

    if( keyboard.key[ SDL_SCANCODE_W ] )
    {
        if( ninjaC.counter == 0 )
            ninjaC.counter = 1;
    }

    if( keyboard.key[ SDL_SCANCODE_A ] )
    {
        if( ninjaC.rect.x > 0 )
        {
            ninjaC.rect.x -= ninjaC.speed;
            ninjaC.value = 1;

            if( shurikenC.value == 2 )
                shurikenC.value = 0;
        }
    }
    else if( keyboard.key[ SDL_SCANCODE_D ] )
    {
        if( ninjaC.rect.x <= screen_width / 2 )
            ninjaC.rect.x += ninjaC.speed;
        else
        {
            backgroundC.point.x -= backgroundC.speed;

            if( backgroundC.point.x == -1020 )
                backgroundC.point.x = 0;

            chartC.rect.x += backgroundC.speed * 2;
        }

        ninjaC.value = 1;

        if( shurikenC.value == 0 )
            shurikenC.value = 2;
    }
    else
        ninjaC.value = 0;


    if( ninjaC.counter == 1 )
    {
        if( ninjaC.rect.y > 435 - 72 && ninjaC.rect.y < 470 - 72 )
            ninjaC.rect.y -= ninjaC.speed / 2 + 2;
        else if( ninjaC.rect.y > 470 - 72 && ninjaC.rect.y < 505 - 72 )
            ninjaC.rect.y -= ninjaC.speed / 2 + 4;
        else if( ninjaC.rect.y > 505 - 72 && ninjaC.rect.y < 540 - 72 )
            ninjaC.rect.y -= ninjaC.speed / 2 + 6;
        else if( ninjaC.rect.y > 540 - 72 && ninjaC.rect.y < 720 - 128 - 72 )
            ninjaC.rect.y -= ninjaC.speed / 2 + 8;
        else
            ninjaC.rect.y -= ninjaC.speed / 2;

        if( ninjaC.rect.y <=  350 )    ninjaC.counter = 2;
    }

    if( ninjaC.counter == 2 )
    {
        if( ninjaC.rect.y > 435 - 72 && ninjaC.rect.y < 470 - 72 )
            ninjaC.rect.y += ninjaC.speed / 2 + 2;
        else if( ninjaC.rect.y > 470 - 72 && ninjaC.rect.y < 505 - 72 )
            ninjaC.rect.y += ninjaC.speed / 2 + 4;
        else if( ninjaC.rect.y > 505 - 72 && ninjaC.rect.y < 540 - 72 )
            ninjaC.rect.y += ninjaC.speed / 2 + 6;
        else if( ninjaC.rect.y > 540 - 72 && ninjaC.rect.y < 720 - 128 - 72 )
            ninjaC.rect.y += ninjaC.speed / 2 + 8;
        else
            ninjaC.rect.y += ninjaC.speed / 2;

        if( ninjaC.rect.y >= 543 )         ninjaC.counter = 0;
    }
}

SDL_Rect Control::get_ninja_rect()
{
    return ninjaC.rect;
}

SDL_Rect Control::get_shuriken_rect()
{
    return shurikenC.rect;
}

uint8_t Control::get_ninja_value()
{
    if( ninjaC.counter != 0 )                                       return 2;
    else if( shurikenC.counter > 1 && shurikenC.counter < 40 )      return 3;
    else                                                            return ninjaC.value;
}

uint8_t Control::get_shuriken_value()
{
    if( shurikenC.counter == 0 )        return 1;
    else if( shurikenC.counter > 1 )    return 2;
    else                                return 0;
}


void Control::map_keyboard_control()
{
    if( keyboard.key[ SDL_SCANCODE_Z ] )
    {
        chartC.type ++;

        if( chartC.type == 14 )
            chartC.type = 0;

        SDL_Delay( 200 );
    }
    else if( keyboard.key[ SDL_SCANCODE_A ] )
    {
        chartC.rect.x -= 1024;
        SDL_Delay( 200 );
    }
    else if( keyboard.key[ SDL_SCANCODE_D ] )
    {
        chartC.rect.x += 1024;
        SDL_Delay( 200 );
    }
}

std::string Control::int_to_string( int n )
{
    std::string tmp;
    if( n < 0 )
    {
        tmp = "-";
        n = -n;
    }
    if( n > 9 )
        tmp += int_to_string( n / 10 );

    tmp += n % 10 + 48;

    return tmp;
}

std::string Control::get_block()
{
    while( SDL_PollEvent( &mouse.event ) != 0 )
    {
        if( mouse.event.type == SDL_QUIT )
            SDL_Quit();

        if( mouse.event.type == SDL_MOUSEMOTION )
            SDL_GetMouseState( &mouse.point.x, &mouse.point.y );

        if( mouse.event.type == SDL_MOUSEBUTTONDOWN )
        {
            std::string _new;

            _new += int_to_string( chartC.type ) + '.';
            _new += int_to_string( mouse.point.x + chartC.rect.x ) + '.';
            _new += int_to_string( mouse.point.y ) + '.';

            SDL_Delay( 200 );

            return _new;
        }
    }

    return "F";
}

SDL_Point Control::get_map_mouse_point()
{
    if( chartC.type > 2 )
    {
        for( uint8_t i = 0; i < 10; i++ )
        {
            if( mouse.point.x > 128 * i && mouse.point.x < 128 * ( i + 1 ) )            mouse.point.x = 128 * i;
            if( mouse.point.y > 128 * i + 80 && mouse.point.y < 128 * ( i + 1 ) + 80 )  mouse.point.y = 128 * i + 80;
        }
    }

    return mouse.point;
}

SDL_Rect Control::get_map_rect()
{
    return chartC.rect;
}

uint8_t Control::get_type_block()
{
    return chartC.type;
}


void Control::check_collision( SDL_Rect &a, SDL_Rect b ) // a = postac, b = blok, p = precyzja
{
    uint8_t p = 5;
    // sztuczna grawitacja
    a.x --;

    // po lewej stronie
    if( a.x + a.w > b.x && a.x + a.w < b.x + p && a.y + a.h > b.y && a.y < b.y + b.h )
        a.x -= ( a.x + a.w - b.x );

    // po prawej stronie
    else if( a.x < b.x + b.w && a.x > b.x + b.w - p && a.y + a.h > b.y && a.y < b.y + b.h )
        a.x += ( b.x + b.w - a.x );

    // od gory
    if( a.y + a.h > b.y && a.y + a.h < b.y + p && a.x + a.w > b.x && a.x < b.x + b.w )
        a.y -= ( a.y + a.h - b.y );

    // od dolu
    else if( a.y < b.y + b.h && a.y > b.y + b.h - p && a.x + a.w > b.x && a.x < b.x + b.w )
        a.y += ( b.y + b.h - a.y );
}
