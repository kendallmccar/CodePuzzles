// K McCarthy 2022

#include <iostream>
#include <vector>

// https://leetcode.com/problems/maximum-product-subarray/
// Given an integer array nums, find a contiguous non - empty subarray within the array that has the largest product, and return the product.
// The test cases are generated so that the answer will fit in a 32 - bit integer.
// A subarray is a contiguous subsequence of the array.

int MaxProduct(std::vector<int>& nums) {
	// current highest running positive product
	int max_running_product = 1;
	// current lowest running product, so that negative values can cancel each other out later
	int min_running_product = 1;
	// store first item as current max product
	int max_product = nums.at(0);
	for (int i = 0; i < nums.size(); i++) {
		int current_value = nums.at(i);
		// update running products
		max_running_product *= current_value;
		min_running_product *= current_value;
		// if a new negative value has caused max pos / max neg values to invert, swap them
		if (current_value < 0)
			std::swap(max_running_product, min_running_product);
		// if current values are higher or lower than current running products, update them
		max_running_product = std::max(current_value, max_running_product);
		min_running_product = std::min(current_value, min_running_product);
		// update max product if current running product is higher
		max_product = std::max(max_running_product, max_product);
	}
	return max_product;
}

void TestMaxProduct() {
	std::vector<int> nums = { 1,-3,2,0,-1,0,-2,-3,1,2,-3,2 };
	int max_product = MaxProduct(nums);
	std::cout << max_product << std::endl;
}