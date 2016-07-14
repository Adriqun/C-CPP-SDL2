#include <iostream>
#include <typeinfo>

using namespace std;

int main()
{
    unsigned uX;

    if( typeid( uX ) == typeid( unsigned ) )
    {
        cout << "Swietnie, nasz kompilator dziala ;D\n";
    }


    if( typeid( uX ) != typeid( uX / 0.618 ) )
    {
        cout << "\nNo prosze, tutaj tez jest dobrze :)\n";
    }

    int _int;
    unsigned int _unsigned_int;
    char _char;


    cout << "\nNazwa zmiennej int to: " << typeid( _int ).name() << endl;
    cout << "Nazwa zmiennej unsigned int to: " << typeid( _unsigned_int ).name() << endl;
    cout << "Nazwa zmiennej char to: " << typeid( _char ).name() << endl;


    return 0;
}
