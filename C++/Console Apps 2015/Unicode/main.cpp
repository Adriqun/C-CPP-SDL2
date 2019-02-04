#include <iostream>

using namespace std;

int main()
{
    /* Year-Month-Day*/
    /* 2016-06-11 */
    wchar_t litera; // wide char
    wstring napis; // wide string
    napis = L"Szeroki napis"; // poprzedzamy litera L

    wcout << napis << endl;

    return 0;
}
