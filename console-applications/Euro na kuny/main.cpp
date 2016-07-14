#include <iostream>

using namespace std;
class Liczba
{
public:
    float liczba;
    void jedyna()
    {
        cout << "Wpisz euro: " << endl;
        cin>>liczba;
        cout<<"Ilosc Kun: "<<(liczba*740)/100<<endl;
    }
};
int main()
{
        Liczba l;
        l.jedyna();
    return 0;
}
