#include <iostream>

using namespace std;
class Cos
{
    public:
    int test,wynik[1000];
    float c[1000],k[1000],w[1000];
    void wczytaj_wypisz()
    {
        cin>>test;
        for (int i=1; i<=test ; i++)
        {
            cin>>c[i]>>k[i]>>w[i];
            wynik[i]=c[i]*w[i];
        }
        for (int i=1; i<=test ; i++)
        {
            if(wynik[i]<=k[i])
                cout<<"yes"<<endl;
            else
                cout<<"no"<<endl;
        }
    }
};
int main()
{
    Cos zmienna;
    zmienna.wczytaj_wypisz();
    return 0;
}
