#include <iostream>
#include <cmath>
using namespace std;
int x_1,y_1,x_2,y_2,d;
int main()
{
    // pierwiastkowanie to w zasadzie potegowanie ulamkami
    //przyklad sqrt z 4 to 2
    // a 4 podniesione do potegi 1/2 to tez 2
    cout<<"Pierwiastek 4 stopnia z 16 wynosi: "<<pow(16,1.0/4.0)<<endl;
    cout<<"Pierwiastek z 27 wynosi: "<<cbrt(27)<<endl;

    cout<<"Wprowadz pierwsze wspolrzedne x i y: ";
    cin>>x_1>>y_1;
    cout<<endl<<"Wprowadz drugie wspolrzedne x i y: ";
    cin>>x_2>>y_2;
    cout<<"Przekatna wynosi:";
    cout <<sqrt(pow(x_1-x_2,2)+pow(y_1-y_2,2))<< endl;
    return 0;
}
