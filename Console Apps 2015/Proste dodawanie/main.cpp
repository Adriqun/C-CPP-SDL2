#include <iostream>

using namespace std;
int liczba[1000000],suma=0,ile_liczb,testy,brat[1000000],c;
int main()
{   cin>>testy;
for(int b=1;b<=testy;b++)
{
    c++;//glupio myslec ze c jest ciagle zwiekszane tak na prawde nie co chwile a co kazde zakonczenie petli i to byl moj blad [*];
    cin>>ile_liczb;
    for (int i=1;i<=ile_liczb;i++)
    {
    cin>>liczba[i];
    suma+=liczba[i];
    }
    brat[c]=suma;
    suma=0;
}
for(int b=1;b<=testy;b++)
    cout<<brat[b]<<endl;


    return 0;
}
