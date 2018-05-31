#include "list.h"
#include "person.h"


int main()
{
	List <Person>* people = new List <Person>;

	people->print();

	people->add(new Person("Jacob", 15));
	people->add(new Person("Maggie", 40));
	people->add(new Person("Ann", 31));
	people->add(new Person("Susan", 7));
	people->add(new Person("Bart", 67));
	people->add(new Person("Harry", 32));
	people->add(new Person("Annette", 24));

	std::cout << "Before:\n";
	people->print();

	people->remove(new Person("Susan", 7));

	std::cout << "After:\n";
	people->print();

	delete people;
	people = nullptr;

	return 0;
}