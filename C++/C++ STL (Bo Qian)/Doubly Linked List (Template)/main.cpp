#include <iostream>
#include "animal.h"
#include "list.h"

int main()
{
	List<Animal>* list = new List<Animal>;

	list->push_back(new Dog("Sparky", 10, 5));
	list->push_front(new Cat("Gus", 5, 9));
	list->push_front(new Cat("Bo", 1, 1));
	list->push_back(new Dog("Rex", 3, 4));
	list->push_back(new Cat("Duke", 8, 7));

	list->erase(list->search(new Cat("Bo", 1, 1)));
	list->erase(new Cat("Duke", 8, 7));

	List<Animal>* list2 = new List<Animal>;
	list2->swap(list);

	delete list;
	list = nullptr;

	std::cout << "Size: " << list2->size() << std::endl;
	list2->print();

	delete list2;
	list2 = nullptr;

	return 0;
}