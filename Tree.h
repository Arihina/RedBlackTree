#pragma once
#include <iostream>
#include <iomanip>

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

	NodePointer findMin(NodePointer node)
	{
		while (node->left != leaf)
		{
			node = node->left;
		}

		return node;
	}

	NodePointer findMax(NodePointer node)
	{
		while (node->right != leaf)
		{
			node = node->right;
		}

		return node;
	}

	void switchNode(NodePointer node1, NodePointer node2)
	{
		if (node1->parent == nullptr)
		{
			root = node2;
		}
		else if (node1 == node1->parent->left)
		{
			node1->parent->left = node2;
		}
		else
		{
			node1->parent->right = node2;
		}
		node2->parent = node1->parent;
	}

	void leftRotation(NodePointer node)
	{
		NodePointer temp = node->right;
		node->right = temp->left;

		if (temp->left != leaf)
		{
			temp->left->parent = node;
		}

		temp->parent = node->parent;

		if (node->parent == nullptr)
		{
			this->root = temp;
		}
		else if (node == node->parent->left)
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
		else if (node == node->parent->right)
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

	void fixAfterRemove(NodePointer node)
	{
		NodePointer temp;
		while (node != root && node->color == 0)
		{
			if (node == node->parent->left)
			{
				temp = node->parent->right;

				if (temp->color == 1)
				{
					temp->color = 0;
					node->parent->color = 1;
					leftRotation(node->parent);
					temp = node->parent->right;
				}

				if (temp->left->color == 0 && temp->right->color == 0)
				{
					temp->color = 1;
					node = node->parent;
				}
				else
				{
					if (temp->right->color == 0)
					{
						temp->left->color = 0;
						temp->color = 1;
						rightRotation(temp);
						temp = node->parent->right;
					}

					temp->color = node->parent->color;
					node->parent->color = 0;
					temp->right->color = 0;
					leftRotation(node->parent);
					node = root;
				}
			}
			else
			{
				temp = node->parent->left;
				if (temp->color == 1)
				{
					temp->color = 0;
					node->parent->color = 1;
					rightRotation(node->parent);
					temp = node->parent->left;
				}

				if (temp->right->color == 0 && temp->left->color == 0)
				{
					temp->color = 1;
					node = node->parent;
				}
				else
				{
					if (temp->left->color == 0)
					{
						temp->right->color = 0;
						temp->color = 1;
						leftRotation(temp);
						temp = node->parent->left;
					}

					temp->color = node->parent->color;
					node->parent->color = 0;
					temp->left->color = 0;
					rightRotation(node->parent);
					node = root;
				}
			}
		}
		node->color = 0;
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

	void remove(int value)
	{
		NodePointer node = leaf;
		NodePointer nodeRoot = root;

		while (nodeRoot != leaf)
		{
			if (nodeRoot->value == value)
			{
				node = nodeRoot;
				break;
			}

			if (node->value > value)
			{
				nodeRoot = nodeRoot->right;
			}
			else
			{
				nodeRoot = nodeRoot->left;
			}
		}

		if (node == leaf)
		{
			cout << "Impossible to find this value in the tree" << endl;
			exit(1);
		}

		NodePointer temp1, temp2;
		temp2 = node;
		int copyColor = temp2->color;

		if (node->left == leaf)
		{
			temp1 = node->right;
			switchNode(node, node->right);
		}
		else if (node->right == leaf)
		{
			temp1 = node->left;
			switchNode(node, node->left);
		}
		else
		{
			temp2 = findMin(node->left);
			copyColor = temp2->color;
			temp1 = temp2->right;

			if (temp2->parent == node)
			{
				temp1->parent = temp2;
			}
			else
			{
				switchNode(temp2, temp2->right);
				temp2->right = node->right;
				temp2->right->parent = temp2;
			}

			switchNode(node, temp2);
			temp2->left = node->left;
			temp2->left->parent = temp2;
			temp2->color = node->color;
		}

		delete node;
		if (copyColor == 0)
		{
			fixAfterRemove(temp1);
		}
	}

	void byPass(NodePointer node) {
		if (node != leaf) {
			cout << node->value << " ";
			byPass(node->left);
			byPass(node->right);
		}
	}

	void printValue()
	{
		byPass(root);
	}
};