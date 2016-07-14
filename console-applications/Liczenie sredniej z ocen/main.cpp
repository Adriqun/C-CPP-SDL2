#include <iostream>
#include <cstdlib>
using namespace std;
float oceny[10000];
int m,c,a;
float suma,srednia;

int main()
/*
{
    cout << "Wpisz oceny kolejno z przerwami ze spacja" << endl;
    cin >> oceny[1],oceny[2],oceny[3],oceny[4],oceny[5];
    m=oceny[1]+oceny[2]+oceny[3]+oceny[4]+oceny[5];
    c=m/5;
    cout<<c<<endl;
    return 0;
}*/
{
    cout<<"Zakoncz program klikajac dowolna literke"<<endl;

    for (int i=0;i<10000000000;i++)
    {
        cout<<"Wpisz ocene nr. "<<i+1<<endl;
        cin >> oceny[i];
        /*suma=suma+oceny[i];*/
        suma += oceny[i];
        if (oceny[i]==false)
        {
         srednia=suma/5;
         cout<<"Srednia wynosi: "<<srednia<<endl;
         exit (0);
        }
    }








}
