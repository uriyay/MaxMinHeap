#include <iostream>

#include "MaxMinHeap.h"

int main(int argc, const char* argv[])
{
	int array[] = { 1,2,3,4,5 };
	MaxMinHeap heap(array, sizeof(array)/sizeof(int));
	heap.display();

	return 0;
}