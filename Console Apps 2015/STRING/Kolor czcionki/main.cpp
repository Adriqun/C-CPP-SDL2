#include <iostream>
#include <windows.h>


using namespace std;

int main()
{
    for(int i=1;i<=50;i++)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),i);
        cout<<"TEKST: NR-"<<i<<endl;
    }

    return 0;
}
