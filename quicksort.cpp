// K McCarthy 2022

#include <algorithm>
#include <iostream>
#include <math.h>
#include <vector>

// simple quicksort implementation

namespace quicksort {

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

	int Partition(std::vector<int>& v, int lo_index, int hi_index) {
		// use midpoint as pivot
		int pivot = floor((lo_index + hi_index) / 2);
		int pivot_value = v.at(pivot);

		// create working indices
		// index will be incremented/decrimented before first value comparison, so offset index by one
		int curr_lo_index = lo_index - 1;
		int curr_hi_index = hi_index + 1;

		while (true) {
			// move low index to the right until finding a value greater than the pivot
			do { curr_lo_index++; } while (v.at(curr_lo_index) < pivot_value);
			// move high index to the left until finding a value less than the pivot
			do { curr_hi_index--; } while (v.at(curr_hi_index) > pivot_value);
			// when the indices cross, return high index value
			if (curr_lo_index >= curr_hi_index)
				return curr_hi_index;
			// swap the values once matching higher/lower pair found
			std::swap(v.at(curr_lo_index), v.at(curr_hi_index));
		}
	}

	void QuicksortHelper(std::vector<int>& v, int lo_index, int hi_index) {
		// recursive method to partition array into two parts at pivot point
		// continue until running out of valid indices / indices cross
		if (lo_index >= 0 && hi_index >= 0 && hi_index > lo_index) {
			int pivot = Partition(v, lo_index, hi_index);
			QuicksortHelper(v, lo_index, pivot);
			QuicksortHelper(v, pivot + 1, hi_index);
		}
	}

	void Quicksort(std::vector<int>& v) {
		// no sorting needed if fewer than 2 items
		if (v.size() <= 1)
			return;
		QuicksortHelper(v, 0, v.size() - 1);
	}

	bool TestQuicksort() {
		// non-sorted robust test case with duplicates
		std::vector<int> random_vector = { 9, 4, 13, 6, 7, 6, 1, 1, 3, 18, 16 };
		// already sorted vector
		std::vector<int> sorted_vector = { 1, 2, 3, 4, 5 };
		// unusual test case
		std::vector<int> repeat_vector = { 0, 0, 0, 0, 0, 0 };
		// test
		Quicksort(random_vector);
		Quicksort(sorted_vector);
		Quicksort(repeat_vector);
		bool success = IsSorted(random_vector) && IsSorted(sorted_vector) && IsSorted(repeat_vector);
		std::cout << "Quicksort Test Success: " << success << std::endl;
		return success;
	}

}; // end namespace quicksort