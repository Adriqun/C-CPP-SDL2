#include <string>
#include <iostream>
#include <conio.h>

int main()
{
    std::string strImie;
    std::cout << "Podaj swoje imie: ";
    std::cin >> strImie;
    std::cout << "Twoje imie to " << strImie << "." << std::endl;
    getch();

    return 0;
}
