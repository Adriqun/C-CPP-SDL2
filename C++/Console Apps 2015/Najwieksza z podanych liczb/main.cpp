#include <iostream>

using namespace std;
float a,b,c,m;
int main()
{
    cout << "Wpisz trzy liczby oddzielone spacja: ";
    cin>>a>>b>>c;
    m=a;
    if (m<b) m=b;
    if (m<c) m=c;
    cout<<"Najwieksza liczba to: "<<m;
    return 0;
}
