#include <iostream>

using namespace std;
string wyraz;
int liczba;
int main()
{
    cout << "Wpisz dowolny jeden wyraz: ";
    cin >> wyraz;
    liczba = wyraz.length();

    for (int i=liczba;i>=0;i--)
    {
        cout<<wyraz[i];
    }





    return 0;
}
