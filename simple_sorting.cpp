// K McCarthy 2022

#include <algorithm>
#include <iostream>
#include <vector>

// Practice writing simple sorting algorithms

namespace simple_sort {

	class SimpleSorting {
	public:
		SimpleSorting() = default;
		~SimpleSorting() = default;

		void SelectionSort(std::vector<int>& v) {
			if (!PresortChecks(v))
				return;
			// all values preceeding partition index are already sorted
			for (int partition_index = 0; partition_index < v.size() - 1; ++partition_index) {
				// track index of lowest value
				int min_index = partition_index;
				// traverse entire unsorted portion of array after partition index to find smallest value
				for (int compare_index = partition_index + 1; compare_index < v.size(); ++compare_index) {
					if (v.at(compare_index) < v.at(min_index)) {
						// update index of lowest value
						min_index = compare_index;
					}
				}
				// if lowest value of unsorted portion is less than current partition value, swap them
				if (v.at(min_index) < v.at(partition_index))
					std::swap(v.at(min_index), v.at(partition_index));
			}
		}

		void BubbleSort(std::vector<int>& v) {
			/// This algorithm does not need the presort checks because it efficiently handles sorted data
			/// and screens for arrays smaller than 2 as a matter of course
			/// 
			// all values after the partition_index are sorted, repeat until fully partitioned
			int partition_index = v.size() - 1;
			while (partition_index > 0) {
				// track index of final swap to avoid traversing sorted values
				int new_partition = 0;
				// traverse all unsorted values starting from the left, swapping any unsorted values
				for (int i = 0; i < partition_index; ++i) {
					if (v.at(i) > v.at(i + 1)) {
						std::swap(v.at(i), v.at(i + 1));
						new_partition = i + 1;
					}
				}
				partition_index = new_partition;
			}
		}

		void InsertionSort(std::vector<int>& v) {
			if (!PresortChecks(v))
				return;
			// sort array from left to right, with all values less than i in ordered position
			for (int i = 1; i < v.size(); ++i) {
				// store value to be repositioned so we can make a single move when correct position found
				int second_value = v.at(i);
				int current_index = i - 1;
				while (current_index >= 0 && v.at(current_index) > second_value) {
					v.at(current_index + 1) = v.at(current_index);
					--current_index;
				}
				v.at(current_index + 1) = second_value;
			}
		}

		bool TestAll() {
			// run all tests
			return TestSelectionSort() && TestBubbleSort() && TestInsertionSort();
		}

	private:
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

		bool PresortChecks(std::vector<int>& unsorted_v) {
			// arrays of less than 2 items are not in need of sorting
			if (unsorted_v.size() < 2)
				return false;
			// could optionally call IsSorted method here if expecting to handle sorted / repeat arrays frequently
			return true;
		}

		void SetupTestVectors() {
			// non-sorted robust test case with duplicates
			random_vector_ = { 9, 4, 13, 6, 7, 6, 1, 1, 3, 18, 16 };
			// already sorted vector
			sorted_vector_ = { 1, 2, 3, 4, 5 };
			// unusual test case
			repeat_vector_ = { 0, 0, 0, 0, 0, 0 };
		}

		bool TestSelectionSort() {
			SetupTestVectors();
			// test sorting
			SelectionSort(random_vector_);
			SelectionSort(sorted_vector_);
			SelectionSort(repeat_vector_);
			if (IsSorted(random_vector_) && IsSorted(sorted_vector_) && IsSorted(repeat_vector_))
				return true;
			return false;
		}

		bool TestBubbleSort() {
			SetupTestVectors();
			// test sorting
			BubbleSort(random_vector_);
			BubbleSort(sorted_vector_);
			BubbleSort(repeat_vector_);
			if (IsSorted(random_vector_) && IsSorted(sorted_vector_) && IsSorted(repeat_vector_))
				return true;
			return false;
		}

		bool TestInsertionSort() {
			SetupTestVectors();
			// test sorting
			InsertionSort(random_vector_);
			InsertionSort(sorted_vector_);
			InsertionSort(repeat_vector_);
			if (IsSorted(random_vector_) && IsSorted(sorted_vector_) && IsSorted(repeat_vector_))
				return true;
			return false;
		}

		std::vector<int> random_vector_;
		std::vector<int> sorted_vector_;
		std::vector<int> repeat_vector_;
	};

	bool TestSimpleSorting() {
		SimpleSorting sorter;
		int success = sorter.TestAll();
		std::cout << "Simple Sorting Test Success: " << success << std::endl;
		return success;
	}

}; // end namespace simple_sort