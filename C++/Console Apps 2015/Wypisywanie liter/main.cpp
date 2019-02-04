#include <iostream>
#include <windows.h>
using namespace std;
string zdanie;
int main()
{   cout<<"Wpisz zdanie: "<<endl;
    getline(cin,zdanie);
    int dlugosc=zdanie.length();
    for(int i=0;i<=dlugosc-1;i++)
    {
    Sleep (100);
    cout<<zdanie[i];
    }

    return 0;
}
