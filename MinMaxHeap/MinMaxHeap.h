#pragma once

#define MAX_SIZE (100)

class MinMaxHeap
{
private:
	//TODO: change it to allocate a dynamic size for the array
	//		maybe by using a template
	int *m_array;

public:
	MinMaxHeap(int* array);

	//Returns the index of the left child of i, where i is an index of a vertex
	inline int Left(int i) {
		return 2 * i;
	}

	//Returns the index of the right child of i, where i is an index of a vertex
	inline int Right(int i) {
		return (2 * i) + 1;
	}
};

