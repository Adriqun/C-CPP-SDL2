#include <SFML/Audio.hpp>

using namespace sf;

int main()
{
    Music music;
    music.openFromFile( "Sum 41 - Over My Head.ogg");

    music.setVolume( 20 );
    music.play();

    for(;;)
    {

    }

    return 0;
}
