#include <iostream>
#include <windows.h>
#include <time.h>
using namespace std;
int ile;
clock_t start,stop;
double czas;
void sortowanie(int *tab, int n)
{
    for (int i=1; i<=n; i++)
    {
        for (int j=n-1; j>=1; j--)
        {
            if (tab[j]<tab[j-1])
            {
                int bufor;
                bufor=tab[j-1];
                tab[j-1]=tab[j];
                tab[j]=bufor;

            }
        }
    }
}
int main()
{
    cout<<"BUBBLESORT"<<endl;
    cout << "Ile liczb losowych: ";
    cin>>ile;

    int *tablica;
    tablica=new int [ile];
    srand (time(NULL));
    for (int i=0;i<=ile-1;i++)
    {
        tablica[i]=rand()%100+1;
        //cout<<tablica[i]<<" ";
    }
    cout<<endl<<endl;
    start=clock();
    sortowanie(tablica,ile);

    /*for (int i=0;i<=ile-1;i++)
    {
        cout<<tablica[i]<<" ";
    }*/
    stop=clock();
    czas=(double)(stop-start)/CLOCKS_PER_SEC;
    cout<<"Czas sortowania wynosi: "<<czas<<endl;

    delete []tablica;

    return 0;
}
