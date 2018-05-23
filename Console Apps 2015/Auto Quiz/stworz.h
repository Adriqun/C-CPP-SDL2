#include <iostream>
#include <fstream>
using namespace std;
class Wszystko
{
public:
    fstream plik;
    string pytanie,a,b,poprawna,linia;
    string odpowiedz;
    int punkty,nr_pytania;
    int nr_linii;
    void fzapisu();
    void czyszczenie();
    void wczytywanie();

};
