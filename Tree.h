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
		leaf = new Node();
		leaf->color = 0;
		leaf->left = nullptr;
		leaf->right = nullptr;
		root = leaf;
	}
};