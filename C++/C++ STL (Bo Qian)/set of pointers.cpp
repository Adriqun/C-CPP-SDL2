#include <iostream>
#include <string>
#include <set>
#include <map>

using namespace std;

class Animal {

protected:

	int age;
	int sth;
	string name;

public:
	Animal() {
		age = 0;
		sth = 0;
		name = "";
	}

	virtual ~Animal() {
		age = 0;
		sth = 0;
		cout << name << " is dead" << endl;
		name = "";
	};

	int getAge() {
		return age;
	}

	string make_sound() {
		return (name + ": I have " + to_string(age) + " years\n");
	}

	friend ostream& operator<<(ostream& os, Animal& animal) {
		os << animal.make_sound();
		return os;
	}

	// The operator< doesn't work because pointers inside of set have own function.
	/*virtual bool operator<(const Animal*& animal) const {
		return age < animal->getAge();
	}*/
};

// Solution.
struct AnimalSetOperator {
	bool operator()(Animal* an1, Animal* an2) const {
		return an1->getAge() < an2->getAge();
	}
};

class Dog :public Animal {
public:
	Dog(int age) {
		this->age = age;
		name = "Dog";
		cout << "Dog is born" << endl;
	}
};

class Cat :public Animal {
public:
	Cat(int age) {
		this->age = age;
		name = "Cat";
		cout << "Cat is born" << endl;
	}
};

int main()
{
	set<Animal*, AnimalSetOperator> animals;
	animals.insert(new Dog(7));
	animals.insert(new Cat(1));
	animals.insert(new Cat(12));
	animals.insert(new Dog(9));

	// double * because of pointers
	// cout << **animals.begin();

	for (auto &it : animals) {
		cout << *it;
	}

	// example of how to free a set of pointers
	for (;;) {
		if (animals.empty()) {
			break;
		}

		delete *animals.begin();
		animals.erase(animals.begin());
	}

	cout << animals.size();

	return 0;
}
