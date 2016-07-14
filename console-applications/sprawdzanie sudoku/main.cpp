#include <iostream>
using namespace std;

int main()
{
    bool row[ 9 ][9 ]; //First coord for row, second for number
    bool column[ 9 ][ 9 ];
    bool square[ 3 ][ 3 ][ 9 ];

    int t;
    cin >> t;
    while( t-- )
    {
        //zero arrays
        for( int i = 0; i < 9; i++ )
        {
            for( int j = 0; j < 9; j++ )
            {
                row[ i ][ j ] = false;
                column[ i ][ j ] = false;
            }
        }

        for( int i = 0; i < 3; i++ )
        {
            for( int j = 0; j < 3; j++ )
            {
                for( int k = 0; k < 9; k++ )
                {
                    square[ i ][ j ][ k ] = false;
                }
            }
        }

        int number;
        bool wrong = false;

        for( int i = 0; i < 81; i++ )
        {
            cin >> number;

            if( wrong )
                continue; //I just need to read all the chars.

            if( number > 9 || number < 1 )
            {
                wrong = true;
                continue;
            }

            if( !row[ i / 9 ][ number - 1 ] )  //Check row
            {
                row[ i / 9 ][ number - 1 ] = true;
            }
            else
            {
                wrong = true;
                continue;
            }

            if( !column[ i % 9 ][ number - 1 ])  //Check column
            {
                column[ i % 9 ][ number - 1 ] = true;
            }
            else
            {
                wrong = true;
                continue;
            }

            //Check square
            int squareColumn = ( i % 9 ) / 3;
            int squareRow = ( i / 9 ) / 3;
            if ( !square[ squareRow ][ squareColumn ][ number - 1 ] )
            {
                square[ squareRow ][ squareColumn ][ number - 1 ] = true;
            }
            else
            {
                wrong = true;
                continue;
            }
        }

        if ( !wrong )
        {
            //Check squares
            for( int i = 0; i < 3 && !wrong; ++i )
            {
                for( int j = 0; j < 3 && !wrong; ++j )
                {
                    for( int k = 0; k < 9 && !wrong; ++k )
                    {
                        wrong = !square[ i ][ j ][ k ];
                    }
                }
            }
        }

        if( wrong ) cout << "NIE" << endl;
        else        cout << "TAK" << endl;
    }

    return 0;
}
