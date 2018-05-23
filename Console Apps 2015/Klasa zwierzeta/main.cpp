#include <iostream>

using namespace std;
class Zwierze
{
public:

    string imie;
    string rodzaj;
    int wiek;

    void dodaj_zwierze()
    {
        cout<<"DODAWANIE NOWEGO GATUNKU"<<endl;
        cout<<"Wpisz gatunek zwierzecia: "<<endl;
        cin>>rodzaj;
        cout<<"Wpisz imie zwierzecia: "<<endl;
        cin>>imie;
        cout<<"Wpisz wiek zwierzecia: "<<endl;
        cin>>wiek;
    }

    void daj_glos()
    {
        if (rodzaj=="kot") cout<<rodzaj<<" "<<imie<<" lat "<<wiek<<" MIAU";
        else if (rodzaj=="pies") cout<<rodzaj<<" "<<imie<<" lat "<<wiek<<" HAUHAU";
        else if (rodzaj=="krowa") cout<<rodzaj<<" "<<imie<<" lat "<<wiek<<" MUUUU";
        else if (rodzaj=="kogut") cout<<rodzaj<<" "<<imie<<" lat "<<wiek<<" KUKURYKU";
        else cout<<"Nieznany gatunek!";
    }
};
int main()
{
    Zwierze z1,z2;
    z1.dodaj_zwierze();
    z1.daj_glos();
    cout<<endl<<endl<<endl;
    z2.dodaj_zwierze();
    z2.daj_glos();
    return 0;
}
