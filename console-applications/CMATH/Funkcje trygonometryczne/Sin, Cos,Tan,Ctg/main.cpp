#include <iostream>
#include <cmath>
using namespace std;
float kat;
int main()
{
    cout<<"Wpisz kat: ";
    cin>>kat;
    cout<<endl<<"Sinus: "<<sin(kat*M_PI/180)<<endl;
    cout<<endl<<"Cosinus: "<<cos(kat*M_PI/180)<<endl;
    cout<<endl<<"Tangens: "<<tan(kat*M_PI/180)<<endl;
    cout<<endl<<"Cotanges: "<<1/tan(kat*M_PI/180)<<endl;
    return 0;
}
