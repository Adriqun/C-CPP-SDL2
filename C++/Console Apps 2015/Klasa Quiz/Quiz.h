#include <iostream>
#include <fstream>
using namespace std;
class Klasa
{
public:

    fstream plik;
    string pytanie,a,b;
    int punkty,co;
    string poprawna;
    string odpowiedz;

    void wczytaj();
    void wypisz();
};
