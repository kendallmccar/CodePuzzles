// K McCarthy 2022

#include <algorithm>
#include <iostream>
#include <vector>

// https://leetcode.com/problems/best-time-to-buy-and-sell-stock/
// You are given an array prices where prices[i] is the price of a given stock on the i-th day.
// You want to maximize your profit by choosing a single day to buy one stockand choosing a different day in the future to sell that stock.
// Return the maximum profit you can achieve from this transaction. If you cannot achieve any profit, return 0.

int MaxProfit(std::vector<int>& prices) {
	// no profit to be made if there is only one day of trading
	int best_profit = 0;
	// current min price is first item in the array
	int min_price = prices.at(0);
	for (int i = 1; i < prices.size(); ++i) {
		int todays_price = prices.at(i);
		// if today's price is lower than previously seen minimum, update minimum value
		min_price = std::min(todays_price, min_price);
		// if the profit to be made by selling today is higher than previously seen best profit, update best profit
		best_profit = std::max(best_profit, todays_price - min_price);
	}
	return best_profit;
}

void TestMaxProfit() {
	std::vector<int> prices = {7, 3, 500, 3, 1, 5, 3, 6, 0, 4};
	//std::vector<int> prices = { 7,6,4,3,1 };
	int solution = MaxProfit(prices);
	std::cout << solution << std::endl;
}