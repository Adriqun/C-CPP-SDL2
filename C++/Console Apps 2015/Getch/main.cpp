#include <iostream>
#include <conio.h>
#include <cstdlib>
using namespace std;
char zmienna;
int main()
{
     while (true)
{
    zmienna=getch();
    switch (zmienna)
    {
        case 'a': cout<<"arbuz, "; break;
        case 'b': cout<<"banan, "; break;
        case 'c': cout<<"cytrus, ";break;
        case 'd': cout<<"daktyl, ";break;
        case 'e': exit (0);
        default : system ("cls");
    cout <<"  MENU" << endl;
    cout <<" a-arbuz"<<endl;
    cout <<" b-banan"<<endl;
    cout <<" c-cytrus"<<endl;
    cout <<" d-daktyl"<<endl;
    cout <<" e-koniec programu"<<endl;
    }
    }


    return 0;
}
