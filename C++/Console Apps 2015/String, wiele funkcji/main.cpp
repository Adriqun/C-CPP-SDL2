#include <iostream>
#include <conio.h>
#include <string>
#include <windows.h>
#include <cstdlib>
using namespace std;
string zdanie,wyraz,nowezdanie,wyraz2;
int wybor,pozycja,pozycja2;
int main()
{
    while (true)
    {
    system ("cls");
    cout << "MENU" << endl;
    cout << "1.Uzyj funkcji replace  " << endl;
    cout << "2.Uzyj funkcji insert   " << endl;
    cout << "3.Uzyj funkcji substring" << endl;
    cout << "4.Uzyj funkcji erase    " << endl;
    cout << "5.Laczenie zdan      " << endl;
    cout << "Dowolny klawisz.Koniec programu"<<endl;

    wybor=getch();

    switch (wybor)
    {
    case '1': system ("cls");
    Sleep (1000);
              cout<<"Witaj, funkcja ta sluzy do zamiany wyrazow"<<endl;
              cout<<endl<<"Wpisz zdanie: ";
              getline(cin,zdanie);
              cout<<"Wpisz pozycje: ";
              cin>>pozycja;
              cout<<"Wpisz ilosc zastepowanych liter: ";
              cin>>pozycja2;
              cout<<"Wpisz wyraz: ";
              cin>>wyraz;
              zdanie.replace(pozycja,pozycja2,wyraz);
              cout<<"Uzyskane zdanie:"<<zdanie; Sleep (3000);
              break;

    case '2': system ("cls");
    Sleep (1000);
              cout<<"Witaj, funkcja ta sluzy do dodawania wyrazow"<<endl;
              cout<<endl<<"Wpisz zdanie: ";
              getline(cin,zdanie);
              cout<<"Wpisz pozycje: ";
              cin>>pozycja;
              cout<<"Wpisz wyraz: ";
              cin>>wyraz;
              zdanie.insert(pozycja,wyraz);
              cout<<"Uzyskane zdanie:"<<zdanie;Sleep (3000);
              break;

    case '3': system ("cls");
    Sleep (1000);
              cout<<"Witaj, funkcja ta sluzy do tworzenia nowych zdan"<<endl;
              cout<<endl<<"Wpisz zdanie:";               getline(cin,zdanie);
              cout<<"Wpisz pozycje: ";                           cin>>pozycja;
              cout<<"Wpisz ilosc wyjmowanych liter ";            cin>>pozycja2;
              nowezdanie=zdanie.substr(pozycja,pozycja2);
              cout<<"Uzyskane zdanie:"<<nowezdanie;Sleep (3000);
              break;

    case '4': system ("cls");
    Sleep (1000);
              cout<<"Witaj, funkcja ta sluzy do usuwania wyrazow"<<endl;
              cout<<endl<<"Wpisz zdanie: ";
              getline(cin,zdanie);
              cout<<"Wpisz pozycje: ";
              cin>>pozycja;
              cout<<"Wpisz ilos usuwanych liter: ";
              cin>>pozycja2;
              zdanie.erase(pozycja,pozycja2);
              cout<<"Uzyskane zdanie:"<<zdanie;Sleep (3000);
              break;

    case '5': system ("cls");
    Sleep (1000);
              cout<<"Funkcja ta sluzy do laczenia zdan"<<endl;
              cout<<endl<<"Wpisz pierwsze zdanie: ";
              getline(cin,wyraz);
              cout<<"Wpisz drugie zdanie: "<<endl;
              getline(cin,wyraz2);
              cout<<wyraz+wyraz2;Sleep (3000);

    default:  cout<<endl<<"Dziekuje za skorzystanie z programu :)"<<endl;
    exit (0);
    }

    }

    return 0;
}
