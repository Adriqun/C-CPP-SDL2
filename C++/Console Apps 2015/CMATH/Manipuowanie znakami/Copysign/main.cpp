#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    //funkcja w ktorej zwracana jest wielkosc x i znak od y
    float x,y;
    x=10;   // pobieramy liczbe
    y=-156189;   // pobieramy znak
    cout<<copysign(x,y);
    return 0;
}
