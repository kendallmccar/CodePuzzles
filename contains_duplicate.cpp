// K McCarthy 2022

#include <iostream>
#include <unordered_set>
#include <vector>

// https://leetcode.com/problems/contains-duplicate/
// Given an integer array nums, return true if any value appears at least twice in the array, and return false if every element is distinct.

bool ContainsDuplicate(std::vector<int>& nums) {
	// use an unordered set to store all previously seen values
	std::unordered_set<int> seen;
	for (int i = 0; i < nums.size(); ++i) {
		int current_value = nums.at(i);
		// if the current value is already in the set of previously seen items, duplicate found
		if (seen.count(current_value) > 0)
			return true;
		// else, add to the previously seen set
		seen.insert(current_value);
	}
	// if this step is reached, no duplicates were seen
	return false;
}

void TestContainsDuplicate() {
	std::vector<int> nums = { 1,1,1,3,3,4,3,2,4,2 };
	bool solution = ContainsDuplicate(nums);
	std::cout << solution << std::endl;
}