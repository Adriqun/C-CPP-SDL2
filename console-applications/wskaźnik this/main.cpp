#include <iostream>

using namespace std;

class Arbuz
{

protected:

    uint16_t width, height;

public:

    void setWidth( uint16_t width )
    {
        this -> width = width;
    }

    void setHeight( uint16_t height )
    {
        this -> height = height;
    }
};

class Pelikan
{

public:

    void wypisz( Pelikan &x )
    {
        if( this == &x )
        {
            cout << "Zostal uzyty ten sam obiekt!\n";
        }
        else
            cout << "Uzyto innego obiektu!\n";
    }
};

int main()
{
    Pelikan klasa_pierwsza, klasa_druga;

    klasa_pierwsza.wypisz( klasa_druga );
    klasa_druga.wypisz( klasa_druga );

    return 0;
}
