// K McCarthy 2022

#include <iostream>
#include <vector>

// https://leetcode.com/problems/product-of-array-except-self/
// Given an integer array nums, return an array answer such that answer[i] is equal to the product of all the elements of nums except nums[i].
// The product of any prefix or suffix of nums is guaranteed to fit in a 32 - bit integer
// You must write an algorithm that runs in O(n) time and without using the division operation.
// Solve the problem in O(1) extra space complexity (The output array does not count as extra space for space complexity analysis.)

std::vector<int> ProductExceptSelf(std::vector<int>& nums) {
	int size = nums.size();
	// variable to store running product from left to right
	int left_product = 1;
	// variable to store running product from right to left
	int right_product = 1;
	std::vector<int> solution(size, 1);
	// the idea behind this algorithm is that we will keep a running product starting from both ends of the arrays
	// the first running product to reach index "i" of some value input[i] will be stored in the solution array at solution[i]
	// the second running product to reach index "i" will be multiplied with the running product already stored at solution[i]
	// such that solution[i] = product of all values such that input[<i] * product of all values such that input[>i]
	for (int i = 0; i < size; ++i) {
		int current_value = nums.at(i);
		// multiply the product currently stored at current index in the solution array by
		// the product of all values to the left of current index in the solution array
		solution.at(i) = solution.at(i) * left_product;
		// update the left running product to include the current value
		left_product *= current_value;
		// determine the inverse/mirror index of the current index
		int inverse_index = size - 1 - i;
		// multiply the product currently stored at the inverse index in the solution array by
		// the product of all values to the right of inverse index in the solution array
		solution.at(inverse_index) = solution.at(inverse_index) * right_product;
		// update the right product to include the value at the inverse index
		right_product *= nums.at(inverse_index);
	}
	return solution;
}

void TestProductExceptSelf() {
	std::vector<int> nums = { 1,2,3,4 };
	std::vector<int> solution = ProductExceptSelf(nums);
	for (int i = 0; i < solution.size(); ++i) {
		std::cout << solution.at(i) << " ";
	}
	std::cout << std::endl;
}