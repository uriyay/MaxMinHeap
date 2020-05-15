#include <iostream>
#include <string.h>

#include "MaxMinHeap.h"

//helper methods
bool max_should_replace(int* arr, size_t heap_size, int parent_index, int child_index) {
	if ((child_index <= heap_size) && (arr[child_index] > arr[parent_index]))
		return true;
	return false;
}

bool min_should_replace(int* arr, size_t heap_size, int parent_index, int child_index) {
	if ((child_index <= heap_size) && (arr[child_index] < arr[parent_index]))
		return true;
	return false;
}
//

MaxMinHeap::MaxMinHeap(int *array, size_t array_size) {
	//TODO: consider using vector
	m_array = new int[array_size];
	memcpy(m_array, array, array_size * sizeof(*array));
	m_size = array_size;
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
	if (i % 2 == 0) {
		should_replace_func = &max_should_replace;
	}
	else {
		should_replace_func = &min_should_replace;
	}

	int left_index = left(i);
	int right_index = right(i);

	int to_be_replaced = i;

	if (should_replace_func(m_array, m_heap_size, i, left_index)) {
		to_be_replaced = left_index;
	}
	if (should_replace_func(m_array, m_heap_size, i, right_index)) {
		to_be_replaced = right_index;
	}

	if (to_be_replaced != i) {
		int temp = m_array[i];
		m_array[i] = m_array[to_be_replaced];
		m_array[to_be_replaced] = temp;

		heapify(to_be_replaced);
	}
}

void MaxMinHeap::display()
{
	for (int i = 0; i < m_heap_size; i++) {
		std::cout << i << ":" << i + 1 << ": " << m_array[i] << std::endl;
	}
}