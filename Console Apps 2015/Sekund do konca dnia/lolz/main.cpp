#include <iostream>
#include <windows.h>
using namespace std;
int wiek;
int main()
{
 cout<<"Twoim zadaniem bedzie odpowiedziec poprawnie na pytanie" <<endl;
 Sleep (1000);
 cout<<"Zaczynajmy!" <<endl;
 Sleep (1000);
 cout<<"Ile Patrycja Michalek ma lat?"<<endl;
 cin>> wiek;

 if (wiek==15)
 {
     cout<<"Poprawna odpowiedz!";
 }
 else if (wiek>15)
 {
     cout<<"Zla odpowiedz!";

 }






    return 0;
}
