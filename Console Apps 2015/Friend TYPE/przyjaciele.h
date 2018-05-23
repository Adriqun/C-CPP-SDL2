#include <iostream>

using namespace std;
//Potrzebne w celu uzyskania przyjazni
class Prostokat;
class Punkt
{
    float x,y;
    string nazwa;

public:
    Punkt(string="A",float=0,float=0);
    void wczytaj();
    //ustalamy przyjaciela
    friend void sedzia(Punkt &pkt, Prostokat &p);
};
class Prostokat
{
    float x,y,wysokosc,szerokosc;
    string nazwa;

public:
    Prostokat(string="brak",float=0,float=0,float=1,float=1);
    void wczytaj();
    //ustalamy przyjaciela
    friend void sedzia(Punkt &pkt, Prostokat &p);
};
