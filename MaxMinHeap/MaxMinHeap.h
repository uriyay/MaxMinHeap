#pragma once

#include <math.h>
#include <vector>
#include <iostream>

class MaxMinHeap
{
private:
	//TODO: change it to allocate a dynamic size for the array
	//		maybe by using a template
	std::vector<int> m_array;
	size_t m_heap_size;

public:
	MaxMinHeap(std::vector<int> &array);

	//Returns the index of the left child of i, where i is an index of a vertex in the heap
	inline int left(int i) {
		//2i in 0-based world = 2(i + 1) - 1
		return 2 * i + 1;
	}

	//Returns the index of the right child of i, where i is an index of a vertex in the heap
	inline int right(int i) {
		//2i + 1 in 0-based world = 2(i + 1) + 1 - 1
		return 2 * i + 2;
	}

	//Returns the index of the parent of i, where i is an index of a vertex in the heap
	inline int parent(int i) {
		//round down (i/2)
		return (int)((i - 1) / 2);
	}

	//returns the depth of node at index i
	inline int get_depth(int i) {
		//log2(i) + 1
		//translate to 1-based
		int depth = (int)(log2((double)i + 1));
		return depth;
	}

	inline bool is_on_max_level(int i) {
		int depth = get_depth(i);
		return depth % 2 == 0;
	}

	int extract_max();

	int extract_min();

	void heapify_(int i, bool is_max_level);

	void build_heap();

	void heapify(int i);

	void display();
};

typedef bool (*should_replace_func_t)(std::vector<int> &arr, size_t heap_size, int parent_index, int child_index);