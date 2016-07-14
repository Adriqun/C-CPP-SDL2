#include <iostream>

using namespace std;
float metry;
float ile_cali(float m);
float ile_jardow(float m)
{
    return m*1.09361;
}
void ile_mili(float m)
{
    cout<<"na mile: "<<m*0.000621371<<endl;;
}
void milemorskie(float m)
{
cout<<"na mile morskie: "<<m*0.000539956;
}
int main()
{
    cout << "Wpisz ile metrow: ";
    cin>>metry;
    cout<<"na cale: "<<ile_cali(metry)<<endl;
    cout<<"na jardy: "<<ile_jardow(metry)<<endl;
    ile_mili(metry);
    milemorskie(metry);
    return 0;
}
float ile_cali(float m)
{
   return m*39.37007;
}
