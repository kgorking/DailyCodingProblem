// Given an array of integers, return a new array such that each element at index i of the new array is the product of all the numbers in the original array except the one at i.
// For example, if our input was [1, 2, 3, 4, 5], the expected output would be [120, 60, 40, 30, 24]. If our input was [3, 2, 1], the expected output would be [2, 3, 6].
//  Follow-up: what if you can't use division?

#include <algorithm>
#include <numeric>
#include <iostream>
#include <ranges>
#include <vector>

void print_vec(auto const& vec) {
	for(auto const& e : vec)
		std::cout << e << ' ';
	std::cout << '\n';
}

std::vector<int> exclusive_product_v1(std::vector<int> list) {
	if (list.empty())
		return list;

	int const total = std::accumulate(list.begin(), list.end(), 1, std::multiplies<int>{});

	auto result = list;
	for(int& i : result)
		i = total / i;
	return result;
}

std::vector<int> exclusive_product_v2(std::vector<int> list) {
	if (list.empty())
		return list;

	std::vector<int> result(list.size());
	for (size_t i=0; i<list.size(); i++) {
		result[i] = std::accumulate(list.begin() + 1, list.end(), 1, std::multiplies<int>{});
		std::rotate(list.begin(), list.begin() + 1, list.end());
	}

	return result;
}

std::vector<int> exclusive_product_v3(std::vector<int> const& list) {
	if (list.empty())
		return list;

	std::vector<int> result(list.size());
	int product = 1;
	for (size_t i=0; i<list.size(); i++) {
		result[i] = product;
		product *= list[i];
	}
	product = 1;
	for (auto i=ssize(list)-1; i >= 0; i--) {
		result[i] *= product;
		product *= list[i];
	}
	return result;
}

int main() {
	std::vector const v1{1, 2, 3, 4, 5};

	print_vec(exclusive_product_v1(v1));
	print_vec(exclusive_product_v2(v1));
	print_vec(exclusive_product_v3(v1));

	std::vector const v2{3,2,1};
	print_vec(exclusive_product_v1(v2));
	print_vec(exclusive_product_v2(v2));
	print_vec(exclusive_product_v3(v2));
}
