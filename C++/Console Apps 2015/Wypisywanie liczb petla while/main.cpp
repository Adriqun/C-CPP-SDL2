#include <iostream>
#include <cstdlib>
#include <windows.h>
using namespace std;
int zmienna,i=0;
int main()

{
cout<<"Wpisz rzadana wartosc"<<endl;
cin>>zmienna;
    while (i<zmienna)
    {
    Sleep (100);
    system ("cls");
    i++;
    cout<<i<<endl;
    }




    return 0;
}
