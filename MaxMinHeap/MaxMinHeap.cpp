#include <string.h>

#include "MaxMinHeap.h"

MaxMinHeap::MaxMinHeap(int *array, size_t array_size) {
	//TODO: consider using vector
	m_array = new int[array_size];
	memcpy(m_array, array, array_size);
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
		should_replace_func = max_should_replace;
	}
	else {
		should_replace_func = min_should_replace;
	}

	int left_index = left(i);
	int right_index = right(i);

	int to_be_replaced = i;

	/*if (should_replace_func(i, left_index)) {
		to_be_replaced = left_index;
	}
	if (should_replace_func(i, right_index)) {
		to_be_replaced = right_index;
	}

	if (to_be_replaced != i) {
		int temp = m_array[i];
		m_array[i] = m_array[to_be_replaced];
		m_array[to_be_replaced] = temp;

		heapify(to_be_replaced);
	}*/
}

bool MaxMinHeap::max_should_replace(int parent_index, int child_index) {
	if ((child_index <= m_heap_size) && (m_array[child_index] > m_array[parent_index]))
		return true;
	return false;
}

bool MaxMinHeap::min_should_replace(int parent_index, int child_index) {
	if ((child_index <= m_heap_size) && (m_array[child_index] < m_array[parent_index]))
		return true;
	return false;
}