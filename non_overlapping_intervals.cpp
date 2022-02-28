// K McCarthy 2022

#include <algorithm>
#include <iostream>
#include <vector>

// https://leetcode.com/problems/non-overlapping-intervals/
// Given an array of intervals intervals where intervals[i] = [starti, endi]
// return the minimum number of intervals you need to remove to make the rest of the intervals non-overlapping.
// Constraints:
//   1 <= intervals.length <= 105
//   intervals[i].length == 2
//   - 5 * 104 <= starti < endi <= 5 * 104

// helper method to sort by end time
bool CompareInterval(std::vector<int>& a, std::vector<int>& b) {
	return a.at(0) < b.at(0);
}

int EraseOverlapIntervals(std::vector<std::vector<int>>& intervals) {
	// sort intervals by end time
	std::sort(intervals.begin(), intervals.end(), CompareInterval);
	// track number of intervals erased
	int erased = 0;
	// index for previous interval
	int previous = 0;
	for (int i = 1; i < intervals.size(); ++i) {
		int current_start = intervals.at(i).at(0);
		int current_end = intervals.at(i).at(1);
		int previous_end = intervals.at(previous).at(1);
		// if the current start time is before the previous end, there is a conflict
		if (current_start < previous_end) {
			// and one of them will need to be erased
			++erased;
			if (current_end < previous_end)
				// if the ending time of the current item is sooner, erase the previous item
				// else if the ending time of the previous item is sooner, current will be erased
				previous = i;
		}
		else {
			// if they do not overlap, update previous to hold the current interval for next loop
			previous = i;
		}
	}
	// return number of erase operations
	return erased;
}

void TestEraseOverlapIntervals() {
	std::vector<std::vector<int>> intervals = { {1, 2},{2, 3},{3, 4},{1, 3} };
	int solution = EraseOverlapIntervals(intervals);
	std::cout << solution << std::endl;
}