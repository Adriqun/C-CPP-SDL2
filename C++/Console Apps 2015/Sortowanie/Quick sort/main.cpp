#include <iostream>
#include <time.h>
#include <windows.h>
using namespace std;
int ile;
clock_t start,stop;
double czas;
void quicksort(int *tablica, int lewy, int prawy)
{
    int v=tablica[(lewy+prawy)/2];
    int i,j,x;
    i=lewy;
    j=prawy;
    do
    {
        while (tablica[i]<v) i++;
        while (tablica[j]>v) j--;
        if (i<=j)
        {
            x=tablica[i];
            tablica[i]=tablica[j];
            tablica[j]=x;
            i++;
            j--;
        }
    }
    while (i<=j);
    if (j>lewy) quicksort(tablica,lewy, j);
    if (i<prawy) quicksort(tablica, i, prawy);
}
int main()
{
    cout << "QUICKSORT" << endl;
    cout<<"Ile losowych liczb: "; cin>>ile;
    int *tablica;
    tablica=new int [ile];
    srand(time(NULL));

    for (int i=0;i<=ile-1;i++)
    {
        tablica[i]=rand()%100+1;
        //cout<<tablica[i]<<" ";
    }
    cout<<endl;
    start=clock();
    quicksort (tablica,0,ile-1);
    stop=clock();
    czas=(double)(stop-start)/CLOCKS_PER_SEC;

    /*for (int i=0;i<=ile-1;i++)
    {
        cout<<tablica[i]<<" ";
    }*/
    cout<<endl<<"Czas sortowania wynosi: "<<czas<<" s";
    return 0;
}
