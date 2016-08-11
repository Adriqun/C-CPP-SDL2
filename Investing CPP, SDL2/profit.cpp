#include "profit.h"

void Profit::sortString()
{
    for( unsigned i = 0; i < inputText.length(); i ++ )
    {
        if( inputText[ i ] == ' ' )
        {
            inputText.erase( i, 1 );
        }
    }

    string newInputText = "";
    int c = inputText.length()-1;
    for( unsigned i = 0; i < inputText.length(); i ++ )
    {
        newInputText += inputText[ i ];

        if( c%3 == 0 )
        {
            newInputText += ' ';
        }

        c --;
    }
    inputText = newInputText;
}

// Only +numbers
long long Profit::strToInt( string s )
{
    long long tmp = 0;

    for( unsigned i = 0; i < s.size(); i++ )
    {
        if( s[ i ] == ' ' )
            continue;

        tmp = 10 * tmp + s[ i ] - 48;
    }

    return tmp;
}