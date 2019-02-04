#include <iostream>
#include <cmath>
using namespace std;
int x_1,y_1,x_2,y_2,z_1,z_2;
int main()
{
    // wzor: d= pierwiastek[(x1-x2)^2 + (y1-y2)^2 + (z1-z2)^2]
    cout<<"Podaj pierwsze wspolrzedne x,y i z: ";
    cin>>x_1>>y_1>>z_1;
    cout<<endl<<"Podaj drugie wspolrzedne x,y i z: ";
    cin>>x_2>>y_2>>z_2;

    cout<<endl<<"Odleglosc dwoch punktow wynosi: ";
    cout<<cbrt(pow(x_1-x_2,2) + pow(y_1-y_2,2) + pow(z_1-z_2,2))<<endl;
    return 0;
}
