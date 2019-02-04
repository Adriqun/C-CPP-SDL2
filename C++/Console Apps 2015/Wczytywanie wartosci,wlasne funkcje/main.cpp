#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;
fstream plik;int i;
float linia;
float ile_K(float c)
{
    return c-273.15;
}
float ile_F(float c)
{
    return (c*1.8)+32;
}
int main()
{  plik.open("liczby.txt", ios::out|ios::app);
 while (true)
{   system ("cls");
    cout<<"Wpisz ile stopni Celcjusza: ";
    cin>>linia;
    getchar(); getchar();
    i++;
    plik<<i<<". "<<"Temperatura w stopniach Celcjusza: "<<linia<<endl;
    plik<<"Temperatura w stopniach Kelwina: "<<ile_K(linia)<<endl;
    plik<<"Temperatura w stopniach Fahrenheita: "<<ile_F(linia)<<endl;
}
plik.close();

return 0;
}
