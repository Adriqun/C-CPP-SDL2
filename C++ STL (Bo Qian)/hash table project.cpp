#include <iostream>
#include <string>

using namespace std;

class HashTable {

	struct Item {
		string name;
		string drink;
		Item* next;
	};

	int size;
	Item** table;

public:
	HashTable(int size = 0);
	~HashTable();

	int hash(string key);
	void create(int size);

	int count(int index);					// Counts items.
	bool remove(string name);				// Remove item.
	void add(string name, string drink);	// Add item.
	

	// Print functions.
	void printTable();
	void printBucket(int index);

	// Search.
	void find(string name);
};

HashTable::HashTable(int size) {
	if (size != 0) {
		create(size);
	}
}

HashTable::~HashTable() {
	Item* delItem = nullptr;
	for (int i = 0; i < size; ++i) {
		delItem = table[i];
		while (table[i] != nullptr) {
			delItem = table[i];
			table[i] = table[i]->next;
			delete delItem;
		}
	}

	size = 0;
}



int HashTable::hash(string key) {
	int sum = 0;
	for (auto &it : key) {
		sum += (static_cast <int> (it) * 31);
	}
	
	return (sum %size);
}

void HashTable::create(int size) {
	if (size < 1 ) {
		return;
	}

	this->size = size;
	table = new Item*[size];

	for (int i = 0; i < size; ++i) {
		table[i] = new Item;
		table[i]->name = "";
		table[i]->drink = "";
		table[i]->next = nullptr;
	}
}



int HashTable::count(int index) {
	if (index < 0 || index >= size) {
		return 0;
	}

	int counter = 0;

	if (!table[index]->name.empty()) {
		++counter;
		Item* ptrItem = table[index];
		while (ptrItem->next != nullptr) {
			++counter;
			ptrItem = ptrItem->next;
		}
	}

	return counter;
}

bool HashTable::remove(string name) {
	bool status = false;
	int index = hash(name);

	// If we only have one item in the bucket
	if (table[index]->name == name && table[index]->next == nullptr) {
		table[index]->name = "";
		table[index]->drink = "";
		status = true;
	}

	// There are more items inside bucket and the found is the first in the bucket.
	else if (table[index]->name == name) {
		Item* delItem = table[index];
		table[index] = table[index]->next;
		delete delItem;
		status = true;
	}

	else {
		Item* p1 = table[index]->next;
		Item* p2 = table[index];

		while (p1 != nullptr && p1->name != name) {
			p2 = p1;
			p1 = p1->next;
		}

		// Match found.
		if (p1 != nullptr) {
			Item* delItem = p1->next;
			p2->next = delItem;
			delete p1;
			status = true;
		}
	}

	return status;
}

void HashTable::add(string name, string drink) {
	int index = hash(name);
	
	if (table[index]->name.empty()) {
		table[index]->name = name;
		table[index]->drink = drink;
	}
	else {
		Item* ptrItem = table[index];
		Item* newItem = new Item;
		newItem->name = name;
		newItem->drink = drink;
		newItem->next = nullptr;

		while (ptrItem->next != nullptr) {
			ptrItem = ptrItem->next;
		}
		ptrItem->next = newItem;
	}
}



void HashTable::printTable() {
	for (int i = 0; i < size; ++i) {
		printBucket(i);
	}
}

void HashTable::printBucket(int index) {
	if (index < 0 || index >= size) {
		return;
	}

	Item* ptrItem = table[index];

	cout << "-----------------------\n";
	cout << "#Index: " << index << " | #Items: ";

	if (ptrItem->name.empty()) {
		cout << "0\n";
	}
	else {
		cout << count(index) << endl << endl;
		while (ptrItem != nullptr) {
			cout << "Name: " << ptrItem->name << "  Drink: " << ptrItem->drink << endl;
			ptrItem = ptrItem->next;
		}
	}

	cout << "-----------------------\n\n";
}



void HashTable::find(string name) {
	int index = hash(name);
	bool found = false;
	string drink = "";

	Item* ptrItem = table[index]; // pointing to the first item
	while (ptrItem != nullptr) {
		if (ptrItem->name == name) {
			found = true;
			drink = ptrItem->drink;
		}

		ptrItem = ptrItem->next;
	}

	if (found) {
		cout << "Favorite Drink = " << drink << endl;
	}
	else {
		cout << "Cannot find information" << endl;
	}
}




int main()
{
	HashTable* table = new HashTable(3);
	
	//table->add("Paul", "Locha");
	//table->add("Kim", "Iced Mocha");
	//table->add("Emma", "Smoothy");
	//table->add("Annie", "Hot Chocolate");
	//table->add("Sarah", "Passion Tea");
	//table->add("Pepper", "Caramel Mocha");
	//table->add("Mike", "Apple Cider");
	//table->add("Steve", "Chai Tea");
	//table->add("Bill", "Boot Beer");
	//table->add("Marie", "Skinny Late");
	//table->add("Susan", "Water");
	//table->add("Joe", "Green Tea");
	//
	//// table->remove("Annie");
	//table->printTable();
	//// table->find("Steve");

	delete table;

	return 0;
}
