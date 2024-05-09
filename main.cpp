#include <iostream>
#include "Tree.h"

using namespace std;

int main()
{
    int countNode = 0;
    cout << "Enter a count of nodes for AVL Tree ";
    cin >> countNode;

    if (countNode <= 0)
    {
        cout << "The count of vertices must be greater than 0";
        exit(1);
    }

    Tree tree;
    int value;

    for (int i = 0; i < countNode; i++)
    {
        cout << "Enter a value for node ";
        cin >> value;
        tree.insert(value);
    }

    cout << "Red - Black Tree" << endl;
    tree.print();
    cout << endl;
    cin >> countNode;
}