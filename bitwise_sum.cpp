// K McCarthy 2022

#include <iostream>
#include <stdlib.h>
#include <time.h>

// https://leetcode.com/problems/sum-of-two-integers/
// Given two integers a and b, return the sum of the two integers without using the operators + and -.
// Constraints: -1000 <= a, b <= 1000

int GetSum(int a, int b) {
	// continue until there are no 1's to be carried to the left
	while (b != 0) {
		// if both bits are 1 at any given point, they will need to be carried to the left
		int carryover = a & b;
		// combine all bits that don't have carries
		a = a ^ b;
		// update b to hold the 1's that need to be carried to the left
		// c++ has undefined behavior when bitshifting signed ints to the left, so make unsigned
		b = (unsigned)carryover << 1;
	}
	return a;
}

int GetRandomInt() {
	// utility method to generate random numbers for testing
	return (rand() % 2000) - 1000;
}

bool TestGetSum() {
	// random seed
	srand(time(NULL));
	// generate a random number between  -1000 and 1000;
	int a = GetRandomInt();
	int b = GetRandomInt();
	int solution = GetSum(a, b);
	bool success = solution == a + b;
	return success;
}