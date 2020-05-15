#pragma once

class MaxMinHeap
{
private:
	//TODO: change it to allocate a dynamic size for the array
	//		maybe by using a template
	int *m_array;
	size_t m_size;
	size_t m_heap_size;

public:
	MaxMinHeap(int *array, size_t array_size);

	//Returns the index of the left child of i, where i is an index of a vertex in the heap
	inline int left(int i) {
		//2i in 0-based world = 2(i + 1) - 1
		return (2 * (i + 1)) - 1;
	}

	//Returns the index of the right child of i, where i is an index of a vertex in the heap
	inline int right(int i) {
		//2i + 1 in 0-based world = 2(i + 1) + 1 - 1
		return ((2 * (i + 1)) + 1) - 1;
	}

	//Returns the index of the parent of i, where i is an index of a vertex in the heap
	inline int parent(int i) {
		//round down (i/2)
		return (int)(i / 2);
	}

	void build_heap();

	void heapify(int i);

	void display();
};

typedef bool (*should_replace_func_t)(int *arr, size_t heap_size, int parent_index, int child_index);