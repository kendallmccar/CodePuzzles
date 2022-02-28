// K McCarthy 2022

#include <iostream>
#include <locale> 
#include <string>

// https://leetcode.com/problems/valid-palindrome/
// A phrase is a palindrome if, after converting all uppercase letters into lowercase letters and removing all non - alphanumeric characters,
// it reads the same forwardand backward. Alphanumeric characters include letters and numbers.
// Given a string s, return true if it is a palindrome, or false otherwise.

bool IsPalindrome(std::string s) {
	// work simultaneously from the left and right sides, comparing each alphanumeric character
	size_t left_index = 0;
	size_t right_index = s.length() - 1;
	while (right_index > left_index) {
		// keep incrementing until an alphanumeric character is found
		if (!isalnum(s.at(left_index))) {
			++left_index;
			continue;
		}
		// keep decrimenting until an alphanumeric character is found
		if (!isalnum(s.at(right_index))) {
			--right_index;
			continue;
		}
		// when parallel alphanumeric characters are found, disregard capitalization and compare
		char left_char = std::tolower(s.at(left_index));
		char right_char = std::tolower(s.at(right_index));
		// if non-matching pair is found, it is not a palindrome, end early
		if (left_char != right_char)
			return false;
		// move on to the next set of characters to compare
		++left_index;
		--right_index;
	}
	// no non-matching pairs found, it is a palindrome!
	return true;
}

void TestIsPalindrome() {
	std::string teststring = "A man, a plan, a canal: Panama";
	bool palindromic = IsPalindrome(teststring);
	std::cout << palindromic << std::endl;
}