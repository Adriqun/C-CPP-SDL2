#include <iostream>

using namespace std;
string slowo;
int a;
int main()
{   cout<<"Wpisz slowo: ";
    cin>>slowo;
    cout<<"Wpisz pozycje: ";
    cin>>a;
    char znak=slowo.at(a);
    cout<<znak<<" "<<slowo;
    return 0;
}
