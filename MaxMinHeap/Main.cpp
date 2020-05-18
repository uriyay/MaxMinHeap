#include <iostream>
#include <vector>

#include "MaxMinHeap.h"

int main(int argc, const char* argv[])
{
	std::vector<int> array;
	if (argc < 2) {
		std::cout << "Usage: " << argv[0] << " array" << std::endl;
		std::cout << "where array is a numbers list seperated by comma and surrounded by quotation marks" << std::endl;
		return 1;
	}

	//prepare the array - split argv[1] by spaces
	std::string s_array(argv[1]);
	size_t cur_offset = 0;
	size_t delim_offset = -1;
	while (cur_offset < s_array.length()) {
		delim_offset = s_array.find(' ', cur_offset);
		if (delim_offset == -1) {
			delim_offset = s_array.length();
		}
		std::string s_num = s_array.substr(cur_offset, delim_offset - cur_offset);
		cur_offset = delim_offset + 1;
		if (s_num.length() > 0) {
			array.push_back(atoi(s_num.data()));
		}
	}

	MaxMinHeap heap(array);
	std::cout << "display:" << std::endl;
	heap.display();
	heap.validate();

	return 0;
}