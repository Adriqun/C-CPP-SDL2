#include <iostream>
#include "BST.h"

void preorder(Node* node)
{
	if (!node)
		return;

	std::cout << (char)node->key << " ";
	preorder(node->left);
	preorder(node->right);
}

void inorder(Node* node)
{
	if (!node)
		return;

	inorder(node->left);
	std::cout << (char)node->key << " ";
	inorder(node->right);
}

void postorder(Node* node)
{
	if (!node)
		return;

	postorder(node->left);
	postorder(node->right);
	std::cout << (char)node->key << " ";
}

int main()
{
	char treeKeys[10] = { 'F', 'D', 'J', 'B', 'E', 'G', 'K', 'A', 'C', 'I' };
	BST* tree = new BST;

	for (int i = 0; i < 10; ++i)
		tree->add(treeKeys[i]);

	std::cout << std::endl << "Postorder: ";
	postorder(tree->getRootNode());

	std::cout << std::endl << "Inorder: ";
	inorder(tree->getRootNode());

	std::cout << std::endl << "Preorder: ";
	preorder(tree->getRootNode());

	delete tree;
	tree = nullptr;
	return 0;
}