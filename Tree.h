#pragma once
#include <iostream>

using namespace std;

class Node
{
	int value;
	Node* parent;
	Node* left;
	Node* right;
	// 0 - black | 1 - red 
	int color;
};
