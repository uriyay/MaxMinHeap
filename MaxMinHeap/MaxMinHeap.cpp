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
	m_size = array.size();
	m_heap_size = 0;

	build_heap();
}

void MaxMinHeap::build_heap()
{
	m_heap_size = m_size;
	for (int i = (int)(m_size / 2); i >= 0; i--) {
		heapify(i);
	}
}

void MaxMinHeap::heapify(int i)
{
	//decide if we should max_heapify or min_heapify
	should_replace_func_t should_replace_func;
	std::cout << "----" << std::endl;
	std::cout << "i = " << i << std::endl;
	if ((get_depth(i)) % 2 == 0) {
		std::cout << "max order" << std::endl;
		should_replace_func = &max_should_replace;
	}
	else {
		std::cout << "min order" << std::endl;
		should_replace_func = &min_should_replace;
	}

	int left_index = left(i);
	int right_index = right(i);

	int to_be_replaced = i;

	std::cout << "i:" << i << " = " << m_array[i] << std::endl;
	if (left_index < m_heap_size)
		std::cout << "left:" << left_index << " = " << m_array[left_index] << std::endl;
	if (right_index < m_heap_size)
		std::cout << "left:" << right_index << " = " << m_array[right_index] << std::endl;


	if (should_replace_func(m_array, m_heap_size, i, left_index)) {
		std::cout << "left chosen" << std::endl;
		to_be_replaced = left_index;
	}
	if (should_replace_func(m_array, m_heap_size, i, right_index)) {
		std::cout << "right chosen" << std::endl;
		to_be_replaced = right_index;
	}

	if (to_be_replaced != i) {
		int temp = m_array[i];
		m_array[i] = m_array[to_be_replaced];
		m_array[to_be_replaced] = temp;

		if (i == 0) {
			std::cout << "here0" << std::endl;
		}

		heapify(to_be_replaced);
	}
}

void MaxMinHeap::display()
{
	for (int i = 0; i < m_heap_size; i++) {
		std::cout << i << ":" << i + 1 << ": " << m_array[i] << std::endl;
	}
}

bool MaxMinHeap::validate()
{
	for (int i = 0; i < (int)(m_heap_size / 2); i++) {
		int parent = m_array[i];
		int l = left(i);
		int r = right(i);
		if (get_depth(i) % 2 == 0) {
			if ((l < m_heap_size) && (parent < m_array[l])) {
				return false;
			}
			if ((r < m_heap_size) && (parent < m_array[r])) {
				return false;
			}
		}
		else {
			if ((l < m_heap_size) && (parent > m_array[l])) {
				return false;
			}
			if ((r < m_heap_size) && (parent > m_array[r])) {
				return false;
			}
		}
	}
	return true;
}