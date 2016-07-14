#include <iostream>

using namespace std;

int main()
{

    for( register int i = 0; i < 500000; i++ )
    {
        continue;
        cout << i << endl;
    }

    // modyfikator register sprawia ze nasza zmienna
    // zapisywana jest w rejestrze procesora co ogromnie
    // przyspiesza dzialania na niej

    return 0;
}
