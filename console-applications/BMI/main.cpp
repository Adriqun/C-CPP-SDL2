#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

struct Person
{
    string n;
    float w, h;
    inline float get()  { return w / (h/100 * h/100); };
};

int main()
{
    int t;
    cin >> t;

    Person person;
    vector <Person> people;

    for( int i = 0; i < t; i++ )
    {
        people.push_back( person );
        cin >> people[ i ].n >> people[ i ].w >> people[ i ].h;
    }

    printf( "niedowaga\n" );
    for( unsigned i = 0; i < people.size(); i++ )
    {
        if( people[ i ].get() < 18.5 )
        {
            printf( "%s\n", people[ i ].n.c_str() );
            people.erase( people.begin() + i );   i--;
        }
    }   printf( "\n" );


    printf( "wartosc prawidlowa\n" );
    for( unsigned i = 0; i < people.size(); i++ )
    {
        if( people[ i ].get() >= 18.5  && people[ i ].get() < 25.0 )
        {
            printf( "%s\n", people[ i ].n.c_str() );
            people.erase( people.begin() + i );   i--;
        }
    }   printf( "\n" );


    printf( "nadwaga\n" );
    for( unsigned i = 0; i < people.size(); i++ )
    {
        if( people[ i ].get() >= 25.0 )
        {
            printf( "%s\n", people[ i ].n.c_str() );
            people.erase( people.begin() + i );   i--;
        }
    }   printf( "\n" );

    return 0;
}
