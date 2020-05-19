#pragma once

#include <math.h>
#include <stdint.h>
#include <vector>
#include <iostream>

class MaxMinHeap
{
private:
	//TODO: change it to allocate a dynamic size for the array
	//		maybe by using a template
	std::vector<int> m_array;
	size_t m_heap_size;

	void heapify_(int i, bool is_max_level);

	bool is_valid_(int i);

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

	/*
	Returns the maximum element and remove it from the heap
	*/
	int extract_max();

	/*
	Returns the minimum element and remove it from the heap
	*/
	int extract_min();

	//insert an element to the heap
	void heap_insert(int key);

	//increase the value of element at index i to be equals to key
	void heap_increase_key(int i, int key);

	//delete an element from the heap
	void heap_delete(int i);

	//build the heap
	void build_heap();

	//fix the heap starting from index i
	void heapify(int i);

	//display the heap
	void display();

	/*
	checks if the heap is valid
	Returns: true if the heap is valid, else returns false
	*/
	bool is_valid();

	/*
	sort the array that is being held by the heap
	notice that after calling this function the heap will no longer preserve its heap quality
	*/
	void sort();

	void print_as_array();
};