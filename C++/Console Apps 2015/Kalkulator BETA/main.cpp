#include <iostream>

using namespace std;
string dzialanie;
float j,l,w;
int main()
{
    cout << "Siemka Adrian" << endl;
    cout<<"Jakie dzialanie  chcialbys wykonac :)?"<<endl;
    cout<<"s-dodawanie, o-odejmowanie, m-mnozenie, d-dzielenie ;)"<<endl;
    cin>>dzialanie;
    if (dzialanie=="s")
    {
        cout<<"Wprowadz pierwsza liczbe:"<<endl;
        cin>>j;
        cout<<"Wprowadz druga liczbe:"<<endl;
        cin>>l;
        w=(l+j);
        cout<<"Wynik:"<<w;
     }
    if (dzialanie=="o")
    {
        cout<<"Wprowadz pierwsza liczbe:"<<endl;
        cin>>j;
        cout<<"Wprowadz druga liczbe:"<<endl;
        cin>>l;
        w=(j-l);
        cout<<"Wynik:"<<w;
    }
    if (dzialanie=="m")
    {
        cout<<"Wprowadz pierwsza liczbe:"<<endl;
        cin>>j;
        cout<<"Wprowadz druga liczbe:"<<endl;
        cin>>l;
        w=(j*l);
        cout<<"Wynik:"<<w;
    }
    if (dzialanie=="d")
    {
        cout<<"Wprowadz pierwsza liczbe:"<<endl;
        cin>>j;
        cout<<"Wprowadz druga liczbe:"<<endl;
        cin>>l;
        w=(j/l);
        cout<<"Wynik:"<<endl<<w;
    }


    return 0;
}
