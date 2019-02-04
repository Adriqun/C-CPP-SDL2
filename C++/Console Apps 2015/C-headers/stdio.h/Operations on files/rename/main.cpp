#include <stdio.h>
#include <string>

using namespace std;

int main ()
{
    int result;
    string oldname = "oldname.txt";
    string newname = "newname.txt";

    result= rename( oldname.c_str(), newname.c_str() );

    if ( result == 0 )
        puts ( "File successfully renamed" );
    else
        perror( "Error renaming file" );

    return 0;
}
