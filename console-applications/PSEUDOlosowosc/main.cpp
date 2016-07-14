#include <iostream>
#include <time.h>
#include <cstdlib>
using namespace std;
int liczba;
int main()
{

    srand (time(NULL));
    liczba = rand()%3+1;
    cout<<liczba<<endl;



    return 0;
}
