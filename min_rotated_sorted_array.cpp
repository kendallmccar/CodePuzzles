// K McCarthy 2022

#include <iostream>
#include <vector>

// https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/
// Suppose an array of length n sorted in ascending order is rotated between 1 and n times.
// For example, the array nums = [0, 1, 2, 4, 5, 6, 7] might become :
// [4, 5, 6, 7, 0, 1, 2] if it was rotated 4 times.
// [0, 1, 2, 4, 5, 6, 7] if it was rotated 7 times.
// Notice that rotating an array[a[0], a[1], a[2], ..., a[n - 1]] 1 time results in the array[a[n - 1], a[0], a[1], a[2], ..., a[n - 2]].
// Given the sorted rotated array nums of unique elements, return the minimum element of this array.
// You must write an algorithm that runs in O(log n) time.

int FindMin(std::vector<int>& nums) {
	// This algorithm is a binary search that divides the search space in half after each search
	// It compares a midpoint value to the end value to determine which half to use
	size_t start_index = 0;
	size_t end_index = nums.size() - 1;
	// if the start value is greater than the end value, array portion is still rotated
	while(nums.at(start_index) > nums.at(end_index)) {
		// calculate midpoint
		size_t mid_index = (start_index + end_index) / 2;
		if (nums.at(mid_index) < nums.at(end_index)) {
			// if mid value is less than the end value, keep mid value
			// the lowest value is in the left half of the array portion
			end_index = mid_index;
		}
		else {
			// otherwise, if the mid value is greater than the end, no need to use mid value
			// and the lowest value is in the right half of the array portion
			start_index = mid_index + 1;
		}
	}
	// when the start value is less to the end value, or is the only value in the array range
	// we have found the lowest value
	return nums.at(start_index);
}

void TestFindMin() {
	std::vector<int> nums = { 4,5,6,7,0,1,2 };
	int min = FindMin(nums);
	std::cout << min << std::endl;
}