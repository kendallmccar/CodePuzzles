// K McCarthy 2022

#include <cmath>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>

// Find a^3 + b^3 = c^3 + d^3 while 1 <= a,b,c,d <= 1000
// 
// Are a = int1, b = int2, c = int3, d = int4 different from...
//   a = int2, b = int1, c = int3, d = int4?
//   a = int3, b = int4, c = int1, d = int2?
// Assume no, these are all equivalent
//
// Runtime: O(n^2)
// Brute force solution would be O(n^4)

class CubedPairSumEquivalentsFinder {
public:
	CubedPairSumEquivalentsFinder() = default;
	~CubedPairSumEquivalentsFinder() = default;

	void PrintCubedPairSumEquivalents(int max) {
		// adjust for 0 index because we are storing cubes at index of the base
		// everything previously memoized is saved in case same object is used to run another search
		// only resize to add more memoization space if max is larger than last run
		int container_size = max + 1;
		if ((int)cubed_storage_.size() < (container_size))
			cubed_storage_.resize(container_size);
		max_ = max;
		// main traversal algorithm to find all possible sums of two different cubes up to max base value
		for (int i = 1; i <= max_; ++i) {
			// to prevent duplicates, don't recalculate sum b^3 + a^3 when we already did a^3 + b^3
			for (int j = i + 1; j <= max_; ++j) {
				HandleSum(i, j);
			}
		}
	}

private:
	// std::pair needs a hash function to use a hash map (unordered map)
	struct pairHash {
		template <class T1, class T2>
		std::size_t operator() (const std::pair<T1, T2>& pair) const {
			return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
		}
	};

	std::vector<int> cubed_storage_; // memoizing structure for cubing math
	std::unordered_map<std::pair<int, int>, int, pairHash> sum_storage_; // memoizing structure for cubed sums
	std::unordered_map<int, std::vector<std::pair<int, int>>> reverse_sum_lookup_; // enables reverse lookup of cubes by sum
	int max_ = 1000; // max allowed value of a/b/c/d

	// memoizing function for cubing math
	int HandleCube(int value) {
		// don't recalculate if already stored
		if (cubed_storage_.at(value) != 0)
			return cubed_storage_.at(value);
		int cubed = std::pow(value, 3);
		cubed_storage_[value] = cubed;
		return cubed;
	}

	// memoizing function for cubed sums
	// also prints to console when equivalent cubed sums are found to already be stored
	void HandleSum(int aValue, int bValue) {
		std::pair<int, int> key = std::make_pair(aValue, bValue);
		// don't recalculate if already stored
		if (sum_storage_.count(key) > 0)
			return;
		// calculate sum and add to hash map
		int sum = HandleCube(aValue) + HandleCube(bValue);
		sum_storage_.emplace(key, sum);
		// if there are already pairs that produced this sum, print to console that current pair is equivalent
		if (reverse_sum_lookup_.count(sum) > 0) {
			std::vector<std::pair<int, int> >& equivalent_pairs = reverse_sum_lookup_.at(sum);
			for (int i = 0; i < equivalent_pairs.size(); ++i) {
				std::cout << aValue << "^3 + " << bValue << "^3 = " << equivalent_pairs.at(i).first << "^3 + " 
					<< equivalent_pairs.at(i).second << "^3" << std::endl;
			}
		}
		else {
			// no sums have produced this value yet, so make a new vector and add this pair
			std::vector<std::pair<int, int> > new_pair_vector;
			new_pair_vector.push_back(key);
			reverse_sum_lookup_.emplace(sum, new_pair_vector);
		}
	}
};

void TestCubedPairSumEquivalents() {
	CubedPairSumEquivalentsFinder finder;
	// default is 1000, but other max caps can be used
	finder.PrintCubedPairSumEquivalents(1000);
}