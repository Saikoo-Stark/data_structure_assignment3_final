#include "Trees.h"

int main(int argc, char const *argv[])
{
	// Tree *min = new MinHeap();
	Heap minHeap(1);
	minHeap.menu();
	minHeap.insert(12, "saikoo", 3.2, "CS");
	minHeap.insert(15, "saik", 2.2, "IS");
	cout << "minHeap: ";
	minHeap.print();

	Heap maxHeap(-1);
	maxHeap.insert(12, "sakoo", 3.2, "CS");
	maxHeap.insert(15, "sak", 2.2, "IS");
	cout << "maxHeap: ";
	maxHeap.print();

	return 0;
}
