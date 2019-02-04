#include <iostream>
#include <windows.h>
using namespace std;
int ile;
int main()
{   cout<<"Ile miejsc w tablicy: ";
    cin>>ile;
    int *tablica;
     tablica = new int [ile];
     for(int i=1; i<=ile; i++)
     {
     cout<<(int)tablica<<endl;
     tablica++;
     }
    Sleep(3000);
     delete [] tablica;

    return 0;
}
