#include "binarySearchTree.h"

int main()
{
	BST *tree = createBST();
	Node * find;

	insertItem(tree, 1);
	insertItem(tree, 2);
	insertItem(tree, 3);	

	printf("%d", findElement(tree, 1));

	printf("%d", findElement(tree, 2));
	printf("%d", findElement(tree, 3));
	printf("%d", findElement(tree, 4));
}
