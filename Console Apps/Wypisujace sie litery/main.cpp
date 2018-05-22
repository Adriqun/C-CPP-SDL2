#include <windows.h>
#include <iostream>
#include <string>
#include <time.h>
using namespace std ;
void Podziel(string Napis)
{
   int Dlugosc = Napis.length() ;
   for(int i = 0 ; i < Dlugosc ; i++)
   {
             Sleep(100) ;
      cout << Napis[i] ;

   }
}
int main()
{
  string Tekst = "adrian to kupa, pati to laptop, martyna to miyuki" ;
  Podziel(Tekst) ;
 ;
  return 0 ;
}
