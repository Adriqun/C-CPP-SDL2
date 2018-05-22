#include <iostream>
#include <cmath>
using namespace std;
int x_1,y_1,x_2,y_2;
int main()
{
    // wzor: d= pierwiastek[(x1-x2)^2 + (y1-y2)^2]
    cout<<"Podaj pierwsze wspolrzedne x i y: ";
    cin>>x_1>>y_1;
    cout<<endl<<"Podaj drugie wspolrzedne x i y: ";
    cin>>x_2>>y_2;

    cout<<endl<<"Odleglosc dwoch punktow wynosi: ";
    cout<<sqrt(pow(x_1-x_2,2) + pow(y_1-y_2,2))<<endl;
    return 0;
}
