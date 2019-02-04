#include <iostream>

using namespace std;
int h,g,m,n,z,a;
int main()
{
    cout << "Wpisz aktualna godzine:";
    cin>>h;
    cout<<"Wpisz aktualna minute:";
    cin>>m;
    cout<<"Wpisz aktualna sekunde:";
    cin>>z;
    g= h*3600;
    n=m*60;
    a= 86400-(n+g+z);
    cout<<"Sekund do konca dnia:"<<a;
    return 0;
}
