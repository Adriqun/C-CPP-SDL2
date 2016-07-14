#include <iostream>
#include "adrian.h"

using namespace std;
void w(Ksztalt *x)
{
    x->figura();
}
int main()
{
    Ksztalt *wsk;
    Kolo k;
    Kwadrat kw;
    Trojkat t;
    Trapez tr;
    while(true)
    {
    wsk=&k;
    w(wsk);
    wsk=&kw;
    w(wsk);

    wsk=&t;
    w(wsk);

    wsk=&tr;
    w(wsk);
    }
    return 0;
}
