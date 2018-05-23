#include <iostream>
#include <cmath>
using namespace std;
float x;
int main()
{
    cout <<"Wpisz liczbe zmiennoprzecinkowa: ";
    cin>>x;
    cout<<endl<<"Round (Okragly): "<<round(x)<<endl;//zwyczjanie zaokragli
    cout<<endl<<"Ceiling (Sufit): "<<ceil(x)<<endl;//zaogragli do gory
    cout<<endl<<"Floor (Podloga): "<<floor(x)<<endl;//zaogragli do dolu
    cout<<endl<<"Truncate (Obciac): "<<trunc(x)<<endl;//obetnie to co po przecinku
    return 0;
}
