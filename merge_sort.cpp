// K McCarthy 2022

#include <iostream>
#include <utility>
#include <vector>

// simple merge sort implementation

namespace merge_sort {

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

	std::vector<int> Merge(std::vector<int> sorted_nums_a, std::vector<int> sorted_nums_b) {
		// determine size of merged vector
		int combined_size = sorted_nums_a.size() + sorted_nums_b.size();
		std::vector<int> merged(combined_size);
		size_t a_index = 0;
		size_t b_index = 0;
		for (int i = 0; i < combined_size; ++i) {
			if (b_index == sorted_nums_b.size() ||  // if b array is finished, merge from a
				(a_index < sorted_nums_a.size() &&  // if merging from a, make sure a array has values remaining
					sorted_nums_a.at(a_index) < sorted_nums_b.at(b_index))) { // compare values from a and b
				merged.at(i) = sorted_nums_a.at(a_index);
				++a_index;
			}
			else {
				merged.at(i) = sorted_nums_b.at(b_index);
				++b_index;
			}
		}
		return merged;
	}

	std::vector<int> MergeSortHelper(std::vector<int> v) {
		// This method recursively divides the array until reaching only the individual items
		// It then uses the merge method to re-combine all sorted halves into final sorted array
		// if array only has one item, it is inherently sorted
		if (v.size() == 1)
			return v;
		// Divide in half
		int middle_index = floor(v.size() / 2);
		std::vector<int> left_half(v.begin(), v.begin() + middle_index);
		std::vector<int> right_half(v.begin() + middle_index, v.end());
		// Merge two halves
		std::vector<int> sorted_left = MergeSortHelper(std::move(left_half));
		std::vector<int> sorted_right = MergeSortHelper(std::move(right_half));
		std::vector<int> merged = Merge(std::move(sorted_left), std::move(sorted_right));
		return merged;
	}

	void MergeSort(std::vector<int>& input) {
		// no sorting needed if fewer than 2 items
		if (input.size() <= 1)
			return;
		std::vector<int> solution = MergeSortHelper(std::move(input));
		input.swap(solution);
	}

	bool TestMergeSort() {
		// non-sorted robust test case with duplicates
		std::vector<int> random_vector = { 9, 4, 13, 6, 7, 6, 1, 1, 3, 18, 16 };
		// already sorted vector
		std::vector<int> sorted_vector = { 1, 2, 3, 4, 5 };
		// unusual test case
		std::vector<int> repeat_vector = { 0, 0, 0, 0, 0, 0 };
		// test
		MergeSort(random_vector);
		MergeSort(sorted_vector);
		MergeSort(repeat_vector);
		bool success = IsSorted(random_vector) && IsSorted(sorted_vector) && IsSorted(repeat_vector);
		std::cout << "Merge Sort Test Success: " << success << std::endl;
		return success;
	}

}; // end namespace merge_sort