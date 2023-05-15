#include "Trees.h"
// #include "Avl.cpp"
int main(int argc, char const *argv[])
{
	Heap minHeap(-1), maxHeap(1);
	BST bst;
	AVLTree avl;

	while (1)
	{
		int choice;
		cout << "Choose Data Structure:\n"
			 << "1. BST\n"
			 << "2. AVL\n"
			 << "3. Min Heap\n"
			 << "4. Max Heap\n"
			 << "5. Exit Program\n"
			 << "choice : ";
		cin >> choice;
		if (choice == 1)
			bst.menu();
		else if (choice == 2)
			avl.menu();
		else if (choice == 3)
			minHeap.menu();
		else if (choice == 4)
			maxHeap.menu();
		else if (choice == 5)
			return 0;
		else
			cout << "invalid input, try again..\n";
	}

	return 0;
}
