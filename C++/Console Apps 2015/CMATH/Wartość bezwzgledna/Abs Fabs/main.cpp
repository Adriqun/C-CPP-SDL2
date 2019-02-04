#include <iostream>
#include <cmath>
using namespace std;
float floatt;
int calk;
int main()
//program pokazuje wartosc bezwzgledna z liczby X;
{   cout<<"Wpisz ujemna liczbe zmiennoprzecinkowa: ";
    cin>>floatt;
    cout<<endl<<"Wpisz ujemna liczbe calkowita: ";
    cin>>calk;
    cout<<"Liczba zmiennoprzecinkowa wynosi: "<<fabs(floatt);
    cout<<endl<<"Liczba calkowita wynosi: "<<abs(calk);


    return 0;
}
