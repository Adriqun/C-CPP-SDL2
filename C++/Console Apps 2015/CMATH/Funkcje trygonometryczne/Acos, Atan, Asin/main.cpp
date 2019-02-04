#include <iostream>
#include <cmath>
using namespace std;
float wynik,kat;
int main()
{
    cout <<"Wpisz wynik funkcji trygonometrycznej: ";
    cin>>wynik;
    kat=acos(wynik)*180.0/M_PI;
    cout<<endl <<"Kat za pomoca cosinusa wynosi: "<<kat<<endl;
    kat=asin(wynik)*180.0/M_PI;
    cout<<endl <<"Kat za pomoca sinusa wynosi: "<<kat<<endl;
    kat=atan(wynik)*180.0/M_PI;
    cout<<endl <<"Kat za pomoca tangensa wynosi: "<<kat<<endl;
    return 0;
}
