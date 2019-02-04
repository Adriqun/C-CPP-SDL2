#include <iostream>
#include <fstream>
using namespace std;
string nazwa;
int main()
{
    cout << "Wpisz jaki plik chcesz wczytac" << endl;
    getline(cin,nazwa);
    fstream plik;
    plik.open(plik2=(atoi(nazwa.c_str)),ios::in);

    plik.close();

    return 0;
}
