#include <iostream>

using namespace std;
class Samochod
{
    public:
    string marka,model;
    int rocznik,przebieg;

    void wczytaj()
    {
        cout<<"DODAWANIE NOWEGO SAMOCHODU"<<endl;
        cout<<"Wpisz marke: "<<endl; cin>>marka;
        cout<<"Wpisz model: "<<endl; cin>>model;
        cout<<"Wpisz rocznik: "<<endl; cin>>rocznik;
        cout<<"Wpisz przebieg: "<<endl; cin>>przebieg;
    }

    void wypisz()
    {
        if(marka=="Audi") cout<<marka<<" "<<model<<" rocznik: "<<rocznik<<" przebieg: "<<przebieg;
        else if(marka=="Ferrari") cout<<marka<<" "<<model<<" rocznik: "<<rocznik<<" przebieg: "<<przebieg;
        else if(marka=="Fiat") cout<<marka<<" "<<model<<" rocznik: "<<rocznik<<" przebieg: "<<przebieg;
        else if(marka=="Reno") cout<<marka<<" "<<model<<" rocznik: "<<rocznik<<" przebieg: "<<przebieg;
        else
            cout<<"Nieznana marka!";
    }

};
int main()
{
    Samochod s1,s2,s3;
    s1.wczytaj();
    s1.wypisz();
    cout<<endl<<endl;
    s2.wczytaj();
    s2.wypisz();
    cout<<endl<<endl;
    s3.wczytaj();
    s3.wypisz();
    return 0;
}
