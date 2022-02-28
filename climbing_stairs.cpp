// K McCarthy 2022

#include <algorithm>
#include <iostream>
#include <vector>

// https://leetcode.com/problems/climbing-stairs/
// Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?
// Constraints: 1 <= n <= 45

int ClimbStairs(int n) {
	// we know 1 is lowest value of n, so we can start step 1 as having 1 way to reach
	int current_step = 1;
	int next_step = 0;
	for (int step = 1; step < n; ++step) {	
		// add the ways to reach the current step to the next two steps:
		// the next step will become the current step, so add the current steps to it
		next_step += current_step;
		// the step at next step + 1 will become the new next step,
		// next step + 1 has no paths through it yet, so adding current paths to it is 0 + current step
		// given the new next step will be the same as current step, just swap the values
		std::swap(current_step, next_step);
	}
	// this return is the equivalent of making next step the final current step
	// by adding all the remaining current paths to it
	return current_step + next_step;
}

void TestClimbStairs() {
	int paths = ClimbStairs(6);
	std::cout << paths << std::endl;
}