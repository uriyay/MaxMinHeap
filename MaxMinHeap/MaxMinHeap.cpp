#include <iostream>
#include <string.h>

#include "MaxMinHeap.h"

//helper methods
bool max_should_replace(std::vector<int> &arr, size_t heap_size, int parent_index, int child_index) {
	if ((child_index < heap_size) && (arr[child_index] > arr[parent_index]))
		return true;
	return false;
}

bool min_should_replace(std::vector<int> &arr, size_t heap_size, int parent_index, int child_index) {
	if ((child_index < heap_size) && (arr[child_index] < arr[parent_index]))
		return true;
	return false;
}
//

MaxMinHeap::MaxMinHeap(std::vector<int>& array) {
	//TODO: consider using vector
	m_array = array;
	m_heap_size = 0;

	build_heap();
}

void MaxMinHeap::build_heap()
{
	m_heap_size = m_array.size();
	for (int i = (int)(m_array.size() / 2); i >= 0; i--) {
		heapify(i);
	}
}

void MaxMinHeap::heapify_(int i, bool is_max_level)
{
	int node_to_replace = i;

	int left_child = left(i);
	int right_child = right(i);

	if (left_child < m_array.size() && ((m_array[left_child] < m_array[node_to_replace]) ^ is_max_level))
		node_to_replace = left_child;
	if (right_child < m_array.size() && ((m_array[right_child] < m_array[node_to_replace]) ^ is_max_level))
		node_to_replace = right_child;

	int left_grandchild = left(left_child);
	//the grandchilds are sitting in sequence in the array:
	//left = 2i + 1, right = 2i + 2
	//left of left = 2(2i + 1) + 1 = 4i + 3
	//right of left = 2(2i + 1) + 2 = 4i + 4
	//left of right = 2(2i + 2) + 1 = 4i + 5
	//right of right = 2(2i + 2) + 2 = 4i + 6
	for (int i = 0; i < 4 && left_grandchild + i < m_array.size(); ++i) {
		if ((m_array[left_grandchild + i] < m_array[node_to_replace]) ^ is_max_level) {
			node_to_replace = left_grandchild + i;
		}
	}

	if (i == node_to_replace) {
		// No need to replace i and node_to_replace
		return;
	}

	// replace the parent and node_to_replace
	std::swap(m_array[i], m_array[node_to_replace]);

	// if node_to_replace is a grandchild
	if (node_to_replace - left_child > 1)
	{
		// if node_to_replace's parent > node_to_replace then replace them
		if (((m_array[parent(node_to_replace)] < m_array[node_to_replace]) ^ is_max_level)) {
			std::swap(m_array[parent(node_to_replace)], m_array[node_to_replace]);
		}

		heapify_(node_to_replace, is_max_level);
	}
}

void MaxMinHeap::heapify(int i)
{
	if (is_on_max_level(i)) {
		heapify_(i, true);
	}
	else {
		heapify_(i, false);
	}
}

void MaxMinHeap::display()
{
	for (int i = 0; i < m_heap_size; i++) {
		std::cout << i << ":" << i + 1 << ": " << m_array[i] << std::endl;
	}
}

int MaxMinHeap::extract_max() {
	//The maximum is the root of the binary tree
	return m_array[0];
}

int MaxMinHeap::extract_min() {
	//The minimum is the minimum between the 2 childs of root
	int minimum = 0;
	if (1 < m_array.size()) {
		minimum = m_array[1];
	}
	if ((2 < m_array.size()) && (m_array[2] < minimum)) {
		minimum = m_array[2];
	}
	return minimum;
}