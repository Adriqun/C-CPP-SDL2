#include <iostream>

using namespace std;

void Funkcja()
{
    static int nLicznik = 0;

    ++nLicznik;

    std::cout << "Funkcje wywolano po raz " << nLicznik << std::endl;
}

int main()
{
    std::string strWybor;
    do
    {
        Funkcja();
        std::cout << "Wpisz 'q', aby zakonczyc: ";
        std::cin >> strWybor;
    }
    while ( strWybor != "q" );

    return 0;
}
