#include <iostream>
#include <vector>
#include <conio.h>

#include "MaxMinHeap.h"

using namespace std;

const char separetor[] = "-----------------------------------------------------------------";

const char KEY_BUILD = 'B';
const char KEY_EXIT = 'X';
const char KEY_HEAPIFY = 'H';
const char KEY_INSERT = 'I';
const char KEY_EXTRACT_MAX = 'M';
const char KEY_EXTRACT_MIN = 'N';
const char KEY_DELETE = 'D';
const char KEY_DISPLAY = 'P';
const char KEY_SORT = 'S';
const char KEY_PRINT_ARRAY = 'A';
const char KEY_IS_VALID = 'V';

//_getch
void menu_loop(MaxMinHeap &heap, bool &is_heap_built, bool &should_exit) {
	char key = 0;
	cout << separetor << endl;
	cout << "Menu" << endl << separetor << endl;
	cout << "[" << KEY_BUILD << "] Build a heap from a file" << endl;
	if (is_heap_built) {
		cout << "[" << KEY_DISPLAY << "] Display the heap" << endl;
		cout << "[" << KEY_HEAPIFY << "] Heapify" << endl;
		cout << "[" << KEY_INSERT << "] Insert an element to the heap" << endl;
		cout << "[" << KEY_EXTRACT_MAX << "] Extract the maximal element from the heap" << endl;
		cout << "[" << KEY_EXTRACT_MIN << "] Extract the minimal element from the heap" << endl;
		cout << "[" << KEY_DELETE << "] Delete an element from the heap" << endl;
		cout << "[" << KEY_SORT << "] Sort the array contained by the heap" << endl;
		cout << "[" << KEY_PRINT_ARRAY << "] Print the array contained by the heap" << endl;
		cout << "[" << KEY_IS_VALID << "] Checks the validity of the heap" << endl;
	}
	cout << "[" << KEY_EXIT << "] Exit" << endl;
	cout << separetor << endl;
	cout << "Press a key to continue: ";

	key = toupper(_getch());
	cout << endl;
	
	if ((!is_heap_built) && ((key != KEY_EXIT) && (key != KEY_BUILD))) {
		cout << "Invalid key: " << key << ", heap is not built yet" << endl;
		return;
	}

	switch (key) {
	case KEY_BUILD:
	{
		string filepath;
		cout << "Insert array filepath: ";
		//read filepath from string
		cin >> filepath;
		heap = MaxMinHeap(filepath);
		is_heap_built = true;
	}
	break;
	case KEY_INSERT:
	{
		int key = 0;
		cout << "Insert a new key to insert: ";
		cin >> key;
		heap.heap_insert(key);
	}
	break;
	case KEY_DELETE:
	{
		int i = 0;
		cout << "Insert an index to delete from the heap (1-based): ";
		cin >> i;		
		//translate to 0-based index
		i--;
		heap.heap_delete(i);
	}
	break;
	case KEY_DISPLAY:
	{
		heap.display();
	}
	break;
	case KEY_EXTRACT_MAX:
	{
		cout << "maximum: " << heap.extract_max() << endl;
	}
	break;
	case KEY_EXTRACT_MIN:
	{
		cout << "minimum: " << heap.extract_min() << endl;
	}
	break;
	case KEY_HEAPIFY:
	{
		int i = 0;
		cout << "Insert the index to heapify from (1-based): ";
		cin >> i;
		//translate to 0-based
		i--;
		heap.heapify(i);
	}
	break;
	case KEY_PRINT_ARRAY:
	{
		heap.print_as_array();
	}
	break;
	case KEY_SORT:
	{
		cout << "sorting the array:" << endl;
		heap.sort();
		cout << "result:" << endl;
		heap.print_as_array();
	}
	break;
	case KEY_IS_VALID:
	{
		const char *result = heap.is_valid() ? "true" : "else";
		cout << "is valid: " << result << endl;
	}
	break;
	case KEY_EXIT:
	{
		cout << "Goodbye!" << endl;
		should_exit = true;
	}
	break;
	default:
		cout << "Invalid key: " << key << endl;
	}
}

int main(int argc, const char* argv[])
{
	bool is_heap_built = false;
	bool should_exit = false;
	MaxMinHeap heap;
	
	try {
		while (!should_exit) {
			menu_loop(heap, is_heap_built, should_exit);
		}
	}
	catch (std::runtime_error & err) {
		cout << "Error: " << err.what() << endl;
	}

	return 0;
}