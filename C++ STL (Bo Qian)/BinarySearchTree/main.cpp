#include <cstdlib>
#include <iostream>
#include "BST.h"

int main()
{
	int treeKeys[16] = { 50, 76, 21, 4, 32, 64, 15, 52, 14, 100, 83, 2,  3,  70, 87, 80 };
	BST* tree = new BST;

	tree->print();

	for (int i = 0; i < 16; ++i)
	{
		tree->add(treeKeys[i]);
	}

	tree->remove(50);
	tree->printChildren(50);
	tree->print();
	std::cout << std::endl  << "Smallest: " << *tree->getSmallest() << std::endl;
	std::cout << "Greatest: " << *tree->getGreatest() << std::endl;

	std::cout << tree->size();

	delete tree;
	tree = nullptr;

	/*for (int j = 0; j < 100; ++j)
	{
		tree = new BST;
		for (int i = 0; i < 16; ++i)
		{
			tree->add(treeKeys[i]);
		}
		tree->print();

		delete tree;
		tree = nullptr;
	}*/

	return 0;
}
