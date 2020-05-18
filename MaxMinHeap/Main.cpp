#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "MaxMinHeap.h"

bool read_file_to_vector(const char* path, std::vector<int>& array)
{
	std::ifstream infile(path);
	std::string line;
	if (!infile.is_open()) {
		std::cout << "failed to open file '" << path << "'" << std::endl;
		return false;
	}
	while (std::getline(infile, line)) {
		if (line.length() == 0) {
			//skip empty lines
			continue;
		}
		for (int j = 0; j < line.length(); j++) {
			char c = line[j];
			if (!isdigit(c)) {
				return false;
			}
		}
		array.push_back(atoi(line.data()));
	}
	return true;
}

int main(int argc, const char* argv[])
{
	std::vector<int> array;
	if (argc < 2) {
		std::cout << "Usage: " << argv[0] << " input_file" << std::endl;
		std::cout << "where input_file containts a numbers list, each number in a line" << std::endl;
		return 1;
	}

	if (!read_file_to_vector(argv[1], array)) {
		std::cout << "failed to read file '" << argv[1] << "', invalid file" << std::endl;
		return 1;
	}

	MaxMinHeap heap(array);
	std::cout << "display:" << std::endl;
	heap.display();

	return 0;
}