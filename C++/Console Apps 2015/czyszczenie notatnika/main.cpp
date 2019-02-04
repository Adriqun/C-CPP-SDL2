#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    fstream file;

    // add something
    file.open( "file.txt", ios::out | ios::app );
    file << "cos\n" << "cos2\n" << "cos3\n";
    file.close();

    // czyszczenie notatnika
    file.open( "file.txt", ios::out );
    file << "";
    file.close();

    return 0;
}
