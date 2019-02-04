#include <iostream>

using namespace std;

enum class Color {RED, GREEN, BLUE};
// enum class Color : char { RED = 1, GREEN = 2, BLUE = 3 };

int main()
{
    Color color = Color::GREEN;

    if ( color == Color::RED )
    {
        cout << "Color is red";
    }

    return 0;
}
