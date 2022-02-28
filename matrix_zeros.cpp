// K McCarthy 2022

#include <iostream>
#include <unordered_set>
#include <vector>

// https://leetcode.com/problems/set-matrix-zeroes/
// Given an m x n integer matrix matrix, if an element is 0, set its entire row and column to 0's.
// You must do it in place.
// Constraints:
// m == matrix.length, n == matrix[0].length
// 1 <= m, n <= 200
// - 231 <= matrix[i][j] <= 231 - 1

void SetZeroes(std::vector<std::vector<int>>& matrix) {
	int height = matrix.size();
	int width = matrix.at(0).size();
	// store rows or columns to zero later in sets
	std::unordered_set<int> rows_to_zero;
	std::unordered_set<int> columns_to_zero;
	// traverse entire matrix
	for (int row = 0; row < height; ++row) {
		for (int column = 0; column < width; ++column) {
			// if row or column has a zero, add to the zeroing set
			if (matrix.at(row).at(column) == 0) {
				rows_to_zero.insert(row);
				columns_to_zero.insert(column);
			}
		}
	}
	// set zeroes
	for (int row = 0; row < height; ++row) {
		// check set to see if we need to zero this row
		bool row_wipe = rows_to_zero.count(row) == 1;
		for (int column = 0; column < width; ++column) {
			// check set to see if we need to zero this column
			bool column_wipe = columns_to_zero.count(column) == 1;
			// zero any values in a column or row designated for zeroing
			if (row_wipe || column_wipe)
				matrix.at(row).at(column) = 0;
		}
	}
}

void TestSetZeroes() {
	std::vector<std::vector<int>> matrix(3);
	std::vector<int> v1 = { 0, 1, 2, 0 };
	std::vector<int> v2 = { 3, 4, 5, 2 };
	std::vector<int> v3 = { 1, 3, 1, 5 };
	matrix.at(0) = v1;
	matrix.at(1) = v2;
	matrix.at(2) = v3;
	SetZeroes(matrix);
	for (int i = 0; i < matrix.size(); ++i) {
		for (int j = 0; j < matrix.at(i).size(); ++j) {
			std::cout << matrix.at(i).at(j) << " ";
		}
		std::cout << std::endl;
	}
}