#pragma once
#include <iostream>

class Node;
class Tree;
typedef Node* NodePointer;

using namespace std;

class Node
{
public:
	int value;
	Node* parent;
	Node* left;
	Node* right;
	// 0 - black | 1 - red 
	int color;
};

class Tree
{
private:
	NodePointer root;
	NodePointer leaf;
public:
	Tree()
	{
		leaf = new Node;
		leaf->color = 0;
		leaf->left = nullptr;
		leaf->right = nullptr;
		root = leaf;
	}

	void leftRotation(NodePointer node)
	{
		NodePointer temp = node->right;
		node->right = node->left;

		if (temp->left != leaf)
		{
			temp->left->parent = node;
		}

		temp->parent = node->parent;

		if (node->parent == nullptr)
		{
			this->root = temp;
		}
		else if (node = node->parent->left)
		{
			node->parent->left = temp;
		}
		else
		{
			node->parent->right = temp;
		}

		temp->left = node;
		node->parent = temp;
	}
};