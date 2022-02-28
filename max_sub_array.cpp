// K McCarthy 2022

#include <algorithm>
#include <iostream>
#include <vector>

// https://leetcode.com/problems/maximum-subarray/
// Given an integer array nums, find the contiguous subarray(containing at least one number) which has the largest sum and return its sum.
// A subarray is a contiguous part of an array.

int MaxSubArray(std::vector<int>& nums) {
	// initialize running total to first element in the array
	int running_total = nums.at(0);
	// initialize maximum previously seen total to current running_total
	int max_sum = running_total;
	for (int i = 1; i < nums.size(); ++i) {
		int current_value = nums.at(i);
		// if current value is larger than the sum of the current running total and the current value,
		// start new running total from current value
		running_total = std::max(current_value, running_total + current_value);
		// update max sum if running total is now higher than previously seen max sum
		max_sum = std::max(running_total, max_sum);
	}
	return max_sum;
}

void TestMaxSubArray() {
	std::vector<int> nums = { -2,1,-3,4,-1,2,1,-5,4 };
	int solution = MaxSubArray(nums);
	std::cout << solution << std::endl;
}