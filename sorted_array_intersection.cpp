// K McCarthy 2022

#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

// Find the intersection between two sorted arrays
// 
// Where A = array1_size, B = array2_size
// Runtime: O(A + B)
//
// Less ideal solutions
// O(A * B) -- Go through the entire second array for each value in the first array (works for unsorted)
// O(A * logB) -- Do a binary search of a sorted second array for each value in the first array (requires only 1 array to be sorted)

std::unique_ptr<std::vector<int> > FindIntersection(const std::vector<int>& array1, const std::vector<int>& array2) {
	std::unique_ptr<std::vector<int>> common = std::make_unique<std::vector<int>>();
	// Helper variables
	int array1_index = 0, array1_val = 0, array2_index = 0, array2_val = 0;
	while (array1_index < array1.size() && array2_index < array2.size()) {
		array1_val = array1.at(array1_index);
		array2_val = array2.at(array2_index);
		if (array1_val == array2_val) {
			// Value is the same
			common->push_back(array1_val);
			array1_index++;
			array2_index++;
			continue;
		}
		// If not, find a larger value to replace the smaller of the two values
		if (array1_val > array2_val) {
			array2_index++;
		}
		else {
			array1_index++;
		}
	}
	return common;
}

void TestSortedArrayIntersection() {
	// Test data
	std::vector<int> array1 = { 1, 5, 7 };
	std::vector<int> array2 = { 1, 2, 5, 6, 10 };

	// Find intersection
	std::unique_ptr<std::vector<int>> common = FindIntersection(array1, array2);
		
	// Print results
	if (common->size() == 0) {
		std::cout << "No common values" << std::endl;
	} else {
		std::cout << "Common values: ";
		for (int i = 0; i < common->size(); ++i) {
			std::cout << common->at(i) << " ";
		}
		std::cout << std::endl;
	}
}