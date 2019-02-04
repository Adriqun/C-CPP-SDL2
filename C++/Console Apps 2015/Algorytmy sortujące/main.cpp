//Projekt wykonal Adrian Michalek 2015.10.09 - ...
#include <iostream>
#include <time.h>
#include <windows.h>
#include <stdio.h>
using namespace std;

int ile,*t;
int *tablica,*tablica2,*tablica3,*tablica4,*tablica5,*tablica6;
clock_t start,stop;
double czas;


class Funkcje
{
public:
    void quicksort(int *tab, int lewy, int prawy)
    {
        int v=tab[(lewy+prawy)/2];
        //do pokazania ktora liczba na osi
        int p,q;
        p=lewy;
        q=prawy;
        //petla glowna
        do
        {
            while(tab[p]<v) p++;
            while(tab[q]>v) q--;
            if(p<=q)
            {
                swap(tab[p],tab[q]);
                p++;
                q--;
            }
        }
        while(p<=q);
        //algorytm quicksort zawiera w sobie algorytm partycjonujacy
        if(q>lewy) quicksort(tab,lewy, q);
        if(p<prawy) quicksort(tab, p, prawy);
    }
    void merge(int pocz, int sr, int kon)
    {
        int i,j,q;
        for (i=pocz; i<=kon; i++)
            t[i]=tablica2[i];
        i=pocz;
        j=sr+1;
        q=pocz;
        while (i<=sr && j<=kon)
        {
            if (t[i]<t[j])
                tablica2[q++]=t[i++];
            else
                tablica2[q++]=t[j++];
        }
        while (i<=sr) tablica2[q++]=t[i++];
    }
    void mergesort(int pocz, int kon)
    {
        int sr;
        if (pocz<kon)
        {
            sr=(pocz+kon)/2;
            mergesort(pocz, sr);
            mergesort(sr+1, kon);
            merge(pocz, sr, kon);
        }
    }
///////////////////////////////////////////////////////////////////
    void heapify (int *tab, int heap_size, int i)
    {
        int largest, temp;
        int l=2*i, r=(2*i)+1;
        if (l<=heap_size && tab[l]>tab[i])
            largest=l;
        else largest=i;
        if (r<=heap_size && tab[r]>tab[largest])
            largest=r;
        if (largest!=i)
        {
            temp=tab[largest];
            tab[largest]=tab[i];
            tab[i]=temp;
            heapify(tab,heap_size,largest);
        }
    }
    void budKopiec(int *tab, int rozmiar)
    {
        for (int i=rozmiar/2; i>0; i--)
            heapify(tab,rozmiar, i);
    }
    void sort(int *tab, int rozmiar)
    {
        int temp;
        budKopiec(tab, rozmiar);
        for (int i=rozmiar; i>1; i--)
        {
            temp=tab[i];
            tab[i]=tab[1];
            tab[1]=temp;
            rozmiar--;
            heapify(tab,rozmiar,1);
        }
    }
///////////////////////////////////////////////////////////////////
    void countingsort(int A[], int B[], int k, int rozmiar)
    {
        int *C=new int [k+1];
        for (int i=0; i<=k; i++)
            C[i] = 0;

        for (int i=0; i<rozmiar; i++)
            C[(A[i])]++;
        for (int i = 1; i <= k; i++)
            C[i] += C[i-1];
        for (int i = rozmiar-1; i >= 0; i--)
        {
            B[(C[(A[i])])-1] = A[i];
            C[(A[i])]--;
        }
        delete [] C;
    }
    int najwieksza(int tab[], int n)
    {
        int max=tab[0];
        for (int i=1; i<n; i++)
        {
            if (max<tab[i])
                max=tab[i];
        }
        return max;
    }
    void shellsort (int tab[], int size)
    {
        int j;
        for (int n=size/2; n>0; n/=2)
        {
            for (int i=n; i<size; ++i)
            {
                int temp = tab[i];

                for (j=i; j >= n&&temp < tab[j-n]; j-=n)
                    tab[j] = tab[j - n];

                tab[j] = temp;
            }
        }
    }
};
Funkcje f1;

class CzasiTablice
{
public:
    void k(int c)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),c);
    }
    void wstep()
    {
        cout<<"Test najszybszych ";
        k(14);
        cout<<"algorytm\242w sortuj\245cych"<<endl;
        k(7);
        cout<<"Wypisz ile losowych liczb w tablicy: ";
        cin>>ile;
        cout<<endl;
        srand(time(NULL));
        tablica=new int [ile];
        for(int i=0; i<ile; i++)
            tablica[i]=rand()%100+1;

    }
    void time_start(int c, string sortw)
    {
        cout<<"Sortuje ";
        k(c);
        cout<<sortw;
        k(7);
        start = clock();
    }
    void time_stop()
    {
        stop = clock();
        czas = (double)(stop-start) / CLOCKS_PER_SEC;
        cout<<endl<<"Czas sortowania: "<<czas<<" s"<<endl;
    }
    void all_time()
    {
        tablica6=new int [ile];
        for(int i=0; i<ile; i++)
            tablica6[i]=tablica[i];
        time_start(15,"shellsort");
        f1.shellsort(tablica6,ile);
        time_stop();
        cout<<endl;
        delete [] tablica6;

        tablica3=new int [ile];
        for(int i=0; i<ile; i++)
            tablica3[i]=tablica[i];
        time_start(12,"heapsort");
        f1.sort (tablica3,ile);
        time_stop();
        cout<<endl;
        delete [] tablica3;

        tablica4=new int [ile];
        tablica5=new int [ile];
        for(int i=0; i<ile; i++)
        {
            tablica4[i]=tablica[i];
            tablica5[i]=tablica[i];
        }
        time_start(13,"countingsort");
        f1.countingsort(tablica4,tablica5,f1.najwieksza(tablica4,ile),ile);
        time_stop();
        cout<<endl;
        delete [] tablica4;
        delete [] tablica5;

        tablica2=new int [ile];
        t=new int [ile];
        for(int i=0; i<ile; i++)
            tablica2[i]=tablica[i];
        time_start(11,"mergesort");
        f1.mergesort(0,ile-1);
        time_stop();
        cout<<endl;
        delete [] tablica2;
        delete [] t;

        time_start(10,"quicksort");
        f1.quicksort(tablica, 0, ile-1);
        time_stop();
        cout<<endl;
        delete [] tablica;
    }
};
CzasiTablice c1;
int main()
{
    c1.wstep();
    c1.all_time();
    return 0;
}
