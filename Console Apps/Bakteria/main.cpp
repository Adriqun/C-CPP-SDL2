#include <iostream>

using namespace std;
class Bakteria
{
    public:
    long double bakteria,godzina,i;
    void wczytaj()
    {
        cout<<"Istnieje bakteria ktora co godzine podwaja swoja ilosc"<<endl;
        cout << "Wpisz jaka liczbe ma przekroczyc bakteria, a ja Ci wskaze kiedy to zrobi" << endl;
        cin >>i;
        bakteria=1;
        godzina=1;
        while (bakteria<=i)
        {
            godzina++;
            bakteria=bakteria*2;
        }
    }
    void wypisz()
    {
        cout<<"Ilosc bakterii: "<<bakteria<<", Minelo godzin: "<<godzina<<endl;
    }
};
int main()
{
    Bakteria b1;
    b1.wczytaj();
    b1.wypisz();
    return 0;
}
