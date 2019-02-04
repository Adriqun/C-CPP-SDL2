#include <math.h>
#include <time.h>
#include <iostream>
#include <conio.h>

enum BIORHYTM
{
    PHYSICAL = 23,
    EMOTIONAL = 28,
    INTELECTUAL = 33
};

const double PI = 3.1415926538;


double Biorytm( double days, BIORHYTM cykl )
{
    return 100 * sin( ( 2 * PI / cykl ) * days );
}

int main()
{
    /* trzy struktury, przechowuj¹ce datê urodzenia delikwenta,
    aktualny czas oraz ró¿nicê pomiêdzy nimi */

    tm birth_date = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    tm actual_time = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    tm difference_time = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };


    std::cout << "Podaj date urodzenia" << std::endl;
    std::cout << "- dzien: ";
    std::cin >> birth_date.tm_mday;


    std::cout << "- miesiac: ";
    std::cin >> birth_date.tm_mon;
    birth_date.tm_mon--;

    std::cout << "- rok: ";
    std::cin >> birth_date.tm_year;
    birth_date.tm_year -= 1900;

// pobieramy aktualny czas w postaci struktury
    time_t Czas = time( NULL );
    actual_time = *localtime( &Czas );

// obliczamy ró¿nicê miêdzy nim a dat¹ urodzenia
    difference_time.tm_mday = actual_time.tm_mday - birth_date.tm_mday;
    difference_time.tm_mon = actual_time.tm_mon - birth_date.tm_mon;
    difference_time.tm_year = actual_time.tm_year - birth_date.tm_year;

// przeliczamy to na dni
    double survive_days = difference_time.tm_year * 365.25 + difference_time.tm_mon * 30.4375 + difference_time.tm_mday;


    std::cout << std::endl;
    std::cout << "Twoj biorytm" << std::endl;
    std::cout << "- fizyczny: " << Biorytm( survive_days, PHYSICAL ) << '%' << std::endl;
    std::cout << "- emocjonalny: " << Biorytm( survive_days, EMOTIONAL ) << '%' << std::endl;
    std::cout << "- intelektualny: " << Biorytm( survive_days, INTELECTUAL) << '%' << std::endl;

    getch();

    return 0;
}
