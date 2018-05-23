#include <iostream>
#include <windows.h>
#include <cstdlib>
using namespace std;
int czika;
int main()
{
    {
    cout << "Wpisz liczbe: " << endl;
    if (!(cin>>czika))
    {
    cerr<<"To nie jest liczba";
    }
    else cout<<czika<<endl;
    }return 0;
}
