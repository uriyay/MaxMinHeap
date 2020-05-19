#include <iostream>
#include <string.h>
#include <stdexcept>
#include <limits>

#include "MaxMinHeap.h"

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
	if ((i < 0) || (i >= m_heap_size)) {
		throw std::out_of_range("index out of range");
	}
	int node_to_replace = i;

	int left_child = left(i);
	int right_child = right(i);

	//xor with is_max_level will opposite the result of the comparsion (less becomes bigger)
	if (left_child < m_heap_size && ((m_array[left_child] < m_array[node_to_replace]) ^ is_max_level)) {
		node_to_replace = left_child;
	}
	if (right_child < m_heap_size && ((m_array[right_child] < m_array[node_to_replace]) ^ is_max_level)) {
		node_to_replace = right_child;
	}

	int left_grandchild = left(left_child);
	//the grandchilds are sitting in sequence in the array:
	//left = 2i + 1, right = 2i + 2
	//left of left = 2(2i + 1) + 1 = 4i + 3
	//right of left = 2(2i + 1) + 2 = 4i + 4
	//left of right = 2(2i + 2) + 1 = 4i + 5
	//right of right = 2(2i + 2) + 2 = 4i + 6
	for (int i = 0; (i < 4) && ((size_t)left_grandchild + i < m_heap_size); ++i) {
		if ((m_array[(size_t)left_grandchild + i] < m_array[node_to_replace]) ^ is_max_level) {
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
	if ((i < 0) || (i >= m_heap_size)) {
		throw std::out_of_range("index out of range");
	}

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
		std::cout << i + 1 << ": " << m_array[i] << std::endl;
	}
}

int MaxMinHeap::extract_max() {
	if (m_heap_size < 1) {
		throw std::underflow_error("heap underflow");
	}
	//The maximum is the root of the binary tree
	int max = m_array[0];
	//delete this element by moving the maximum element out of the heap
	std::swap(m_array[0], m_array[m_heap_size - 1]);
	m_heap_size--;
	heapify(0);
	return max;
}

int MaxMinHeap::extract_min() {
	//The minimum is the minimum between the 2 childs of root
	int minimum_index = 0;
	int minimum = 0;
	if (m_heap_size < 3) {
		throw std::underflow_error("heap underflow");
	}
	if (1 < m_heap_size) {
		minimum_index = 1;
	}
	if ((2 < m_heap_size) && (m_array[2] < m_array[minimum_index])) {
		minimum_index = 2;
	}
	minimum = m_array[minimum_index];
	//delete this element by moving the minimum element out of the heap
	std::swap(m_array[minimum_index], m_array[m_heap_size - 1]);
	m_heap_size--;
	heapify(0);
	//return the minimum element
	return minimum;
}

bool MaxMinHeap::is_valid_(int i) {
	if ((i < 0) || (i >= m_heap_size)) {
		throw std::out_of_range("index out of range");
	}

	std::vector<int> queue;
	queue.insert(queue.cbegin(), i);
	while (queue.size() >= 1) {
		//pop
		int cur_node = queue[queue.size() - 1];
		queue.pop_back();

		int left_child = left(cur_node);
		int right_child = left(cur_node);

		if ((left_child >= m_heap_size) && (right_child >= m_heap_size)) {
			//its a leaf
			continue;
		}

		if (is_on_max_level(cur_node)) {
			if ((left_child < m_heap_size) && (m_array[cur_node] < m_array[left_child])) {
				return false;
			}
			if ((right_child < m_heap_size) && (m_array[cur_node] < m_array[right_child])) {
				return false;
			}
		}
		else {
			if ((left_child < m_heap_size) && (m_array[cur_node] > m_array[left_child])) {
				return false;
			}
			if ((right_child < m_heap_size) && (m_array[cur_node] > m_array[right_child])) {
				return false;
			}
		}

		//add left and right
		if (left_child < m_heap_size) {
			queue.insert(queue.cbegin(), left_child);
		}
		if (right_child < m_heap_size) {
			queue.insert(queue.cbegin(), right_child);
		}
	}
	return true;
}

bool MaxMinHeap::is_valid() {
	for (int i = 0; i < (int)(m_heap_size / 2); i++) {
		if (!is_valid_(i)) {
			return false;
		}
	}
	return true;
}

void MaxMinHeap::sort() {
	build_heap();
	for (int i = m_array.size() - 1; i >= 1; i--) {
		std::swap(m_array[0], m_array[i]);
		m_heap_size--;
		heapify(0);
	}
}

void MaxMinHeap::heap_insert(int key) {
	m_array.push_back(std::numeric_limits<int>::min());
	m_heap_size++;
	//incrase from min() to key
	heap_increase_key(m_heap_size - 1, key);
}

void MaxMinHeap::heap_increase_key(int i, int key) {
	if ((i < 0) || (i >= m_heap_size)) {
		throw std::out_of_range("index out of range");
	}
	if (key < m_array[i]) {
		throw std::runtime_error("new key is smaller than current key");
	}
	m_array[i] = key;
	int parent_node = -1;
	while (i > 0) {
		parent_node = parent(i);
		if (is_on_max_level(parent_node)) {
			//parent is on a max level, check if parent is bigger than i
			if (m_array[parent_node] >= m_array[i]) {
				//i is in the right place, so we can stop fixing the heap
				break;
			}
			//i is not in the right place, continue the loop
		}
		else {
			//parent is on a min level, check if parent is less than i
			if (m_array[parent_node] <= m_array[i]) {
				//i is in the right place, so we can stop fixing the heap
				break;
			}
			//i is not in the right place, continue the loop
		}
		//replace parent and i
		std::swap(m_array[parent_node], m_array[i]);
		//continue the loop, where the node that contains the key is at parent_node now
		i = parent_node;
	}
}

void MaxMinHeap::heap_delete(int i) {
	if ((i < 0) || (i >= m_heap_size)) {
		throw std::out_of_range("index out of range");
	}
	heap_increase_key(i, std::numeric_limits<int>::max());
	extract_max();
}

void MaxMinHeap::print_as_array() {
	for (int i = 0; i < m_array.size(); i++) {
		std::cout << m_array[i] << std::endl;
	}
}