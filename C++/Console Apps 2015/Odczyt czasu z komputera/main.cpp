#include <time.h>
#include <iostream>

int main()
{
    time_t czas;
    struct tm* ptr;
    // tm* ptr;


    time( &czas );
    ptr = localtime( &czas );

    char* data = asctime( ptr );
    // std::string data = asctime( ptr );


    std::cout << data;
    return 0;
}
