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

	void rightRotation(NodePointer node)
	{
		NodePointer temp = node->left;
		node->left = temp->right;

		if (temp->right != leaf)
		{
			temp->right->parent = node;
		}

		temp->parent = node->parent;

		if (node->parent == nullptr)
		{
			this->root = temp;
		}
		else if (node = node->parent->right)
		{
			node->parent->right = temp;
		}
		else
		{
			node->parent->left = temp;
		}

		temp->right = node;
		node->parent = temp;
	}

	void fixAfterInsert(NodePointer node)
	{
		NodePointer uncle;

		while (node->parent->color == 1)
		{
			if (node->parent == node->parent->parent->right)
			{
				uncle = node->parent->parent->left;
				if (uncle->color == 1)
				{
					uncle->color = 0;
					node->parent->color = 0;
					node->parent->parent->color = 1;
					node = node->parent->parent;
				}
				else
				{
					if (node == node->parent->left)
					{
						node = node->parent;
						rightRotation(node);
					}

					node->parent->color = 0;
					node->parent->parent->color = 1;
					leftRotation(node->parent->parent);
				}
			}
			else
			{
				uncle = node->parent->parent->right;
				if (uncle->color == 1)
				{
					uncle->color = 0;
					node->parent->color = 0;
					node->parent->parent->color = 1;
					node = node->parent->parent;
				}
				else
				{
					if (node == node->parent->left)
					{
						node = node->parent;
						leftRotation(node);
					}
					node->parent->color = 0;
					node->parent->parent->color = 1;
					rightRotation(node->parent->parent);
				}
			}

			if (node == root)
			{
				break;
			}
		}

		root->color = 0;
	}
	
	void insert(int value)
	{
		NodePointer node = new Node;
		NodePointer pointTree = this->root;
		NodePointer temp = nullptr;

		node->parent = nullptr;
		node->value = value;
		node->left = leaf;
		node->right = leaf;
		node->color = 1;

		while (pointTree != leaf)
		{
			temp = pointTree;
			if (node->value > pointTree->value)
			{
				pointTree = pointTree->right;
			}
			else
			{
				pointTree = pointTree->left;
			}
		}

		node->parent = temp;

		if (temp == nullptr)
		{
			root = node;
		}
		else if (node->value > temp->value)
		{
			temp->right = node;
		}
		else
		{
			temp->left = node;
		}

		if (node->parent == nullptr)
		{
			node->color = 0;
			return;
		}

		if (node->parent->parent == nullptr)
		{
			return;
		}

		fixAfterInsert(node);
	}
};