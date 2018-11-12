#include "BST.h"
#include <iostream>

Node::Node(int key)
{
	this->key = key;
	left = nullptr;
	right = nullptr;
}



BST::BST()
{
	_size = 0;
	root = nullptr;
}

BST::~BST()
{
	/*if (!empty())
	{
		delete root;
		root = nullptr;
	}*/

	_size = 0;
	free(root);
}

int BST::size()
{
	return _size;
}

bool BST::empty()
{
	return root == nullptr;
}



void BST::print()
{
	if (!empty())
	{
		printPrivate(root);
	}
	else
	{
		std::cout << "The tree is empty." << std::endl;
	}
}

void BST::printPrivate(Node* node)
{
	if (node->left != nullptr)	printPrivate(node->left);
	std::cout << node->key << " ";
	if (node->right != nullptr)	printPrivate(node->right);
}

void BST::printChildren(int key)
{
	Node* node = getNode(key);

	if (node != nullptr)
	{
		std::cout << "Parent Node = " << node->key << std::endl;

		node->left != nullptr ?
			std::cout << "Left Child = " << node->left->key << std::endl :
			std::cout << "Left Child = NULL" << std::endl;

		node->right != nullptr ?
			std::cout << "Right Child = " << node->right->key << std::endl :
			std::cout << "Right Child = NULL" << std::endl;

	}
}

bool BST::add(int key)
{
	++_size;
	return addPrivate(key, root);
}

bool BST::addPrivate(int key, Node* node)
{
	// Putting first item.
	if (empty())
	{
		root = new Node(key);
		return true;
	}

	// The key is lesser.
	else if (key < node->key)
	{
		if (node->left != nullptr)
		{
			addPrivate(key, node->left);
		}
		else
		{
			node->left = new Node(key);
			return true;
		}
	}

	// The key is greater.
	else if (key > node->key)
	{
		if (node->right != nullptr)
		{
			addPrivate(key, node->right);
		}
		else
		{
			node->right = new Node(key);
			return true;
		}
	}

	return false;
}

Node* BST::getNode(int key)
{
	if (!empty())
	{
		return getNodePrivate(key, root);
	}

	return nullptr;
}

Node* BST::getNodePrivate(int key, Node* node)
{
	if (node != nullptr)
	{
		if (node->key == key)		return node;
		else if (key < node->key)	return getNodePrivate(key, node->left);
		else						return getNodePrivate(key, node->right);
	}

	return nullptr;
}



int* BST::getRootKey()
{
	if (!empty())
	{
		return &root->key;
	}
	
	return nullptr;
}

Node* BST::getRootNode()
{
	return root;
}



int* BST::getSmallest()
{
	if (!empty())
	{
		return findSmallest(root);
	}
	
	return nullptr;
}

int* BST::findSmallest(Node* node)
{
	if (node->left != nullptr)
	{
		return findSmallest(node->left);
	}

	return &node->key;
}

int* BST::getGreatest()
{
	if (!empty())
	{
		return findGreatest(root);
	}

	return nullptr;
}

int* BST::findGreatest(Node* node)
{
	if (node->right != nullptr)
	{
		return findGreatest(node->right);
	}

	return &node->key;
}



void BST::remove(int key)
{
	if (!empty())
	{
		removePrivate(key, root);
	}
}

void BST::removePrivate(int key, Node* node)
{
	if (root->key == key) // Remove key which is at the top.
	{
		removeRoot();
	}
	else
	{
		if (key < node->key && node->left != nullptr)
		{
			if (node->left->key == key)	removeMatch(node, node->left, true);
			else						removePrivate(key, node->left);
		}
		else if (key > node->key && node->right != nullptr)
		{
			if (node->right->key == key)removeMatch(node, node->right, false);
			else						removePrivate(key, node->right);
		}
	}
}

void BST::removeRoot()
{
	Node* delNode = root;

	// Case 0: 0 children
	if (root->left == nullptr && root->right == nullptr)
	{
		--_size;
		delete root;
		root = nullptr;
		delete delNode;
	}

	// Case 1.1: 1 child on the right
	else if (root->left == nullptr && root->right != nullptr)
	{
		--_size;
		root = root->right;
		delete delNode;
	}
	// Case 1.2: 1 child on the left
	else if (root->left != nullptr && root->right == nullptr)
	{
		--_size;
		root = root->left;
		delete delNode;
	}

	// Case 2: 2 children
	else
	{
		// Smallest in the right subtree.
		int smallest = *findSmallest(root->right);
		removePrivate(smallest, root);
		root->key = smallest;
	}
}

void BST::removeMatch(Node* parent, Node* match, bool left)
{
	Node* delNode = match;

	// No children.
	if (match->left == nullptr && match->right == nullptr)
	{
		--_size;
		left ? parent->left = nullptr : parent->right = nullptr;
		match = nullptr;
		delete delNode;
	}

	// One child.
	else if (match->left == nullptr && match->right != nullptr)
	{
		--_size;
		left ? parent->left = match->right : parent->right = match->right;
		match->right = nullptr;
		match = nullptr;
		delete delNode;
	}
	else if (match->left != nullptr && match->right == nullptr)
	{
		--_size;
		left ? parent->left = match->left : parent->right = match->left;
		match->left = nullptr;
		match = nullptr;
		delete delNode;
	}

	// 2 children.
	else
	{
		int smallest = *findSmallest(match->right);
		removePrivate(smallest, match);
		match->key = smallest;
	}
}

void BST::free(Node* node)
{
	if (node != nullptr)
	{
		if (node->left != nullptr)	free(node->left);
		if (node->right != nullptr)	free(node->right);

		delete node;
	}
}