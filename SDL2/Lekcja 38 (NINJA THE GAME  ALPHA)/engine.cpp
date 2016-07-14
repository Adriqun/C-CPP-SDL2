#include "engine.h"

Engine::Engine()
{
    frame = 0;
    renderer =   NULL;
    window =     NULL;
}

void Engine::load_images()
{
    ninja.load_texture( load_tex( renderer, "images/champion/ninja.png" ) );
    shuriken.load_texture( load_tex( renderer, "images/champion/shuriken.png" ) );

    background.load_texture( load_tex( renderer, "images/wall/bg_white.png" ) );

    for( uint8_t i = 0; i < chart.how_many; i++ )
        chart.load_texture( load_tex( renderer, "images/wall/" + control.int_to_string( i ) + ".png" ) );
}

void Engine::load_music()
{

}

void Engine::load_fonts()
{

}

void Engine::load_files()
{
    chart.load_file();
}

void Engine::close_objects()
{
    chart.close();
    delete &chart;
    delete &control;
    delete &ninja;
    delete &shuriken;
    delete &background;
}






void Engine::start_program()
{
    if( !init() )
        perror( "Blad w inicjacji!\n" );

    if( !create_window( window, control.screen_width, control.screen_height ) )
        perror( "Blad w renderze!\n" );

    if( !create_renderer( renderer, window ) )
        perror( "Blad w renderze!\n" );

    load_images();
    load_music();
    load_fonts();
    load_files();
}

void Engine::draw_program()
{
    Timer timer;

    for( ;; )
    {
        timer.start();

        if( frame == -2 )
        {
            intro.draw( renderer );
            delete &intro;

            frame = 1;
        }

        else if( frame == -1 )
        {
            control.map_keyboard_control();

            background.draw( renderer, control.get_background_point() );
            chart.draw( renderer, control.get_map_rect() );
            chart.draw_block( renderer, control.get_map_mouse_point(), control.get_type_block() );
            chart.add_to_file( control.get_block() );
        }

        else if( frame == 0 )
        {
            // menu
            frame = 1;
        }

        else if( frame == 1 )
        {
            control.ninja_mouse_control();
            control.ninja_keyboard_control();

            background.draw( renderer, control.get_background_point() );
            chart.draw( renderer, control.get_map_rect() );

            ninja.draw( renderer, control.get_ninja_rect(), control.get_ninja_value() );
            shuriken.draw( renderer, control.get_shuriken_rect(), control.get_shuriken_value() );
        }

        else if( frame == 2 )
        {
            // pauza albo smierc
        }

        draw_basic( renderer );

        timer.set_fps();
    }

    delete &timer;
}

void Engine::close_program()
{
    close_objects();

    close_basic( renderer, window );
}
