#include "detector.h"

Detector::Detector()
{
    visible = 4;
    counter = 0;
}

Uint8 Detector::checkCollision( SDL_Rect a, SDL_Rect b ) // a = postac, b = blok
{
    if( counter > 50 )
        counter = 0;

    if( counter != 0 )
        counter ++;

    if( counter == 0 )
    {
        // po lewej stronie
        if( a.x + a.w > b.x && a.x + a.w < b.x && a.y + a.h > b.y && a.y < b.y + b.h )
            counter = 1;

        // po prawej stronie
        if( a.x < b.x + b.w && a.x > b.x + b.w && a.y + a.h > b.y && a.y < b.y + b.h )
            counter = 1;

        // od gory
        if( a.y + a.h > b.y && a.y + a.h < b.y && a.x + a.w > b.x && a.x < b.x + b.w )
            counter = 1;

        // od dolu
        if( a.y < b.y + b.h && a.y > b.y + b.h && a.x + a.w > b.x && a.x < b.x + b.w )
            counter = 1;
    }


    if( counter == 1 )
    {
        if( visible == 4 )          visible = 2;
        else if( visible == 3 )     visible = 0;
        else if( visible == 2 )     visible = 3;
        else if( visible == 1 )     visible = 4;
        else if( visible == 0 )     visible = 1;
    }

    return visible;
}
