#include <iostream>
#include <vector>

using namespace std;

class Box
{

public:
    int number; /* liczba eksponatow w pudelku   */
    int weight; /* aktualna waga pudelka         */

    Box()
    {
        number = 0;
        weight = 0;
    }

};

void funkcja()
{
    int number;     // liczba eksponatow
    int max_weight; // maksymalna waga pudelka
    int weight = 0; // waga jednego eksponatu

    cin >> number >> max_weight;


    Box box;
    vector <Box> boxes;
    boxes.push_back( box );

    for( int i = 0; i < number; i++ )
    {
        cin >> weight;

        for( unsigned i = 0; i < boxes.size(); i++ )
        {
            /* jesli box ma mniej niz 2 eksponaty           */
            /* jesli waga pudelka nie przekroczy dopuszczalnej  */
            if( (boxes[ i ].number < 2) && (boxes[ i ].weight + weight <= max_weight) )
            {
                boxes[ i ].number ++;
                boxes[ i ].weight += weight;
                break;
            }

            if( i == boxes.size() - 1 )
            {
                boxes.push_back( box );
            }
        }
    }

    cout << boxes.size() << endl;
}

int main()
{
    int t;
    cin >> t;
    while( t-- )
    {
        funkcja();
    }

    return 0;
}
