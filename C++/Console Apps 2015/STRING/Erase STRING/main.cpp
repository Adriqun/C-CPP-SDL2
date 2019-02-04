#include <iostream>
int a,q;
using namespace std;
string zdanie;
int main()
{
    cout << "Wpisz zdanie:" << endl;
    getline (cin,zdanie);
    cout<<"Wpisz pozycje: ";
    cin>>q;
    cout<<"Wpisz dlugosc: ";
    cin>>a;
    zdanie.erase (a,q);
    cout<<zdanie;
    return 0;
}
