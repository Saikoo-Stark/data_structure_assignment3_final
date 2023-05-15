#include "Trees.h"
// #include "Avl.cpp"
int main(int argc, char const *argv[])
{
	Heap minHeap(-1), maxHeap(1);
	BST bst;
	// AVLTree avl;

	minHeap.menu();
	maxHeap.menu();
	bst.menu();
	// avl.print_inorder();

	return 0;
}
