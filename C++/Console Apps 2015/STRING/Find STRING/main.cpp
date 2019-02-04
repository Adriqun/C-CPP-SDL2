#include <iostream>
#include <algorithm>
using namespace std;
string nazwa,szukaj,cos;
int main()
{   cout<<"Wprowadz zdanie: ";
    getline(cin,nazwa);
    cout<<"Wprowadz szukane ciag: ";
    getline(cin,szukaj);
    size_t pozycja;
    pozycja=nazwa.find(szukaj);
    if (pozycja!=string::npos)
    {
    cout<<pozycja;
    }
    else cout<<"Ciag nie istnieje";

    return 0;
}
