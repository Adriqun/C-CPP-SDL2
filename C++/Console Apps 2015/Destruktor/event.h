#include <iostream>

using namespace std;

class Event
{

    int day, month, year;
    int hour, minutes;
    string name;

    public:
    void load ();
    void show ();
    Event(string="BRAK",int=1,int=1,int=2015,int=12,int=12);
    ~Event();
};
