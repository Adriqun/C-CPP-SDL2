#include <iostream>

using namespace std;
class Nr_miesiaca
{
public:
    int a;
    void wczytaj()
    {
        cout << "Wpisz numer miesiaca" << endl;
    }
    void wypisz()
    {
        if (!(cin>>a))
        {
            cerr<<"Wprowadzono niepoprawne dane"<<endl;
        }
        switch(a)
        {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            cout<<"Ten miesiac ma 31 dni"<<endl;
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            cout<<"Ten miesiac ma 30 dni"<<endl;
            break;
        case 2:
            cout<<"Ten miesiac ma 28/29 dni"<<endl;
            break;
        default:
            cout<<"Naucz sie ile mamy miesiecy debilu"<<endl;
        }
    }

};
int main()
{
    Nr_miesiaca nr1;
    nr1.wczytaj();
    nr1.wypisz();
    return 0;
}
