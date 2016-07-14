#include <iostream>
#include <vector>

using namespace std;

int main()
{
    typedef int to_jest_int;

    vector < to_jest_int > int_vector;

    //wrzucanie do vectora, itd. .....
    for( uint8_t i =0; i < 20; i++ )
        int_vector.push_back( i );
    // czytaj jakie argumenty potrzebujesz, napisales to 2016.02.27 ;)
/*
assign	      | Usuwa wszystkie istniejące elementy z kontenera, a następnie kopiuje wskazane elementy do kontenera. (metoda)
at	          | Zwraca referencję na element, który znajduje się na podanej pozycji w kontenerze » standard C++ ♦ vector. (metoda)
back	      | Zwraca referencję na ostatni element w kontenerze. (metoda)
begin	      | Zwraca iterator wskazujący na pierwszy element. (metoda)
capacity	  | Zwraca maksymalną liczbę elementów jaką może pomieścić kontener bez wykonywania realokacji pamięci. (metoda)
clear	      | Usuwa wszystkie elementy z kontenera vector. (metoda)
empty	      | Sprawdza czy kontener jest pusty. (metoda)
end	          | Zwraca iterator wskazujący na element będący za ostatnim elementem. (metoda)
erase	      | Usuwa jeden element lub wiele elementów z kontenera vector występujących na podanej pozycji lub w podanym zakresie. (metoda)
front	      | Zwraca referencję na pierwszy element w kontenerze. (metoda)
get_allocator | Zwraca kopię alokatora używanego do tworzenia elementów kontenera » standard C++ ♦ vector. (metoda)
insert	      | Wstawia jeden element lub wiele elementów do kontenera vector na określonej pozycji. (metoda)
max_size	  | Maksymalna możliwa długość tablicy kontenera » standard C++ ♦ vector, wyrażona w liczbie elementów. (metoda)
operator[]	  | Zwraca referencję na element, który znajduje się na podanej pozycji w kontenerze » standard C++ ♦ vector. (operator - metoda)
pop_back	  | Usuwa jeden element z kontenera vector, znajdujący się na jego końcu. (metoda)
push_back	  | Dodaje nowy element na końcu kontenera vector. (metoda)
rbegin	      | Zwraca iterator odwrotny wskazujący na ostatni element. (metoda)
rend	      | Zwraca iterator odwrotny wskazujący na element występujący bezpośrednio przed pierwszym elementem. (metoda)
reserve	      | Rezerwuje tyle miejsca w kontenerze, żeby pomieściła się wskazana liczba elementów bez konieczności wykonywania dodatkowej realokacji pamięci przy ich dodawaniu. (metoda)
resize	      | Ustawia nowy rozmiar kontenera vector. (metoda)
size	      | Zwraca liczbę elementów znajdujących się aktualnie w kontenerze. (metoda)
swap	      | Kontenery » standard C++ ♦ vector zamieniają się posiadanymi danymi. (metoda)
*/

    return 0;
}
