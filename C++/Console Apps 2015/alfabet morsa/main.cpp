#include <iostream>
#include <ctype.h>
using namespace std;

int main()
{
    string tab[ 26 ] =
    {
        ".-", "-...", "-.-.", "-..", ".",
        ".-..", "--.", "....", "..", ".---",
        "-.-", "..-.", "--", "-.", "---",
        ".--.", "--.-", ".-.", "...", "-",
        "..-", "...-", ".--", "-..-", "-.--",
        "--.."
    };

    string line;
    while( getline( cin, line ) )
    {
        for( unsigned i = 0; i < line.size(); i++ )
        {
            unsigned nr = static_cast< int >( line[ i ] );

            if( nr > 96 && nr < 123 )
            {
                nr -= 32;
            }

            if( line[ i ] != ' ' )
            {
                cout << tab[ nr - 65 ];
                cout << '/';
            }
            else
            {
                cout << '/';
            }
        }
        cout << endl;
    }

    return 0;
}
