// K McCarthy 2022

#include <iostream>
#include <vector>

void PrintVector(std::vector<int>& int_vector) {
	// prints vector to console
	for (int i = 0; i < int_vector.size(); ++i) {
		std::cout << int_vector.at(i) << " ";
	}
	std::cout << std::endl;
}

bool IsSorted(std::vector<int>& v) {
	// checks if data is sorted
	for (int i = 1; i < v.size() - 1; ++i) {
		if (v.at(i) < v.at(i - 1))
			return false;
	}
	return true;
}

void Heapify(std::vector<int>& v) {

}

void BuildMaxHeap(std::vector<int>& v) {

}

void HeapSort(std::vector<int>& v) {
	// vectors of less than 2 items do not need sorting
	if (v.size() <= 1)
		return;

}

int main2() {
	// non-sorted robust test case with duplicates
	std::vector<int> random_vector = { 9, 4, 13, 6, 7, 6, 1, 1, 3, 18, 16 };
	// already sorted vector
	std::vector<int> sorted_vector = { 1, 2, 3, 4, 5 };
	// unusual test case
	std::vector<int> repeat_vector = { 0, 0, 0, 0, 0, 0 };
	// test
	HeapSort(random_vector);
	HeapSort(sorted_vector);
	HeapSort(repeat_vector);
	bool success = IsSorted(random_vector) && IsSorted(sorted_vector) && IsSorted(repeat_vector);
	std::cout << "Heap Sort Test Success: " << success << std::endl;
	//return success;
	return 0;
}