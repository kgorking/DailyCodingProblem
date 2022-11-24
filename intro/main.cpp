// "return a new sorted merged list from K sorted lists, each with size N"

#include <algorithm>
#include <cppcoro/generator.hpp>
#include <iostream>
#include <ranges>
#include <vector>

// time: KN log KN
// space: KN
auto merge_lists_v1(std::ranges::range auto const& lists) {
	std::vector<int> merged(lists.size() * lists[0].size());
	std::ranges::partial_sort_copy(std::views::join(lists), merged);
	return merged;
}

// time: KN
// space: K
cppcoro::generator<const int> merge_lists_v2(std::ranges::range auto const& lists) {
	int const size = static_cast<int>(lists.size());
	std::vector<int> iterators(lists.size(), 0);

	auto const is_valid = [&](int i) { return i < size; };

	while (std::ranges::any_of(iterators, is_valid)) {
		auto it_min = std::ranges::min_element(iterators, [&](int const& it1, int const& it2) {
			if (it1 == size)
				return false;
			if (it2 == size)
				return true;
			auto const dist1 = std::distance<int const*>(iterators.data(), &it1);
			auto const dist2 = std::distance<int const*>(iterators.data(), &it2);
			return lists[dist1][it1] < lists[dist2][it2];
		});

		auto const dist = std::distance(iterators.begin(), it_min);
		int const index = (*it_min)++;
		co_yield lists[dist][index];
	}
}

int main() {
	std::vector const v1{10, 15, 30};
	std::vector const v2{12, 15, 20};
	std::vector const v3{17, 20, 32};
	auto const vecs = std::vector{v1, v2, v3};

	for (int x : merge_lists_v1(vecs))
		std::cout << x << ' ';
	std::cout << '\n';

	for (int x : merge_lists_v2(vecs))
		std::cout << x << ' ';
	std::cout << '\n';
}
