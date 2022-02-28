// K McCarthy 2022

#include <iostream>
#include <unordered_map>
#include <vector>

// https://leetcode.com/problems/two-sum/
// Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.
// You may assume that each input would have exactly one solution, and you may not use the same element twice.
// You can return the answer in any order.

std::vector<int> TwoSum(std::vector<int>& v, int target) {
	// store seen numbers as keys, with value of their index
	std::unordered_map<int, int> visited;
	std::vector<int> solution;
	for (int i = 0; i < v.size(); ++i) {
		int current_value = v.at(i);
		int companion = target - current_value;
		// check if current value's companion is in the previously seen set
		if (visited.count(companion) > 0) {
			// if so, solution is found
			int companion_index = visited.at(companion);
			solution.push_back(companion_index);
			solution.push_back(i);
			return solution;
		}
		// otherwise, add current value to the visited set
		visited.insert({current_value, i});
	}
	// no solution found
	return solution;
}

void TestTwoSum() {
	std::vector<int> int_vector = { 3, 3, 2, 4, 1 };
	int target = 7;
	std::vector<int> solution = TwoSum(int_vector, target);
	for (int i = 0; i < solution.size(); ++i) {
		std::cout << solution.at(i) << " ";
	}
	std::cout << std::endl;
}