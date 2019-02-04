#include <iostream>
#include "event.h"

using namespace std;

void Event::load()
{
    cout<<"Nazwa wydarzenia: ";
    cin>>name;
    cout<<endl<<"Dzien: ";
    cin>>day;
    cout<<endl<<"Miesiac: ";
    cin>>month;
    cout<<endl<<"Rok: ";
    cin>>year;
    cout<<endl<<"Godzina: ";
    cin>>hour;
    cout<<endl<<"Minuta: ";
    cin>>minutes;
}
void Event::show()
{
    cout<<endl<<name<<" "<<day<<"."<<month<<"."<<year<<" "
    <<hour<<":"<<minutes<<endl;
}

Event::Event(string n,int d,int m,int r,int g,int mins)
{
    name=n;
    day=d;
    month=m;
    year=r;
    hour=g;
    minutes=mins;
}
Event::~Event()
{
    cout<<"Destruktor jest aktywny"<<endl;
}
