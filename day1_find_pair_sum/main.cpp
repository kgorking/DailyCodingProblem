// "Given a list of numbers and a number k, return whether any two numbers from the list add up to k."
// For example, given [10, 15, 3, 7] and k of 17, return true since 10 + 7 is 17.
//   Bonus: Can you do this in one pass?

#include <algorithm>
#include <iostream>
#include <ranges>
#include <vector>

// Sort the list and then walk it from opposite ends. i -> <- j
// If the sum is too small, try a larger i.
// If the sum is too large, try a smaller j.
int count_k_summed(int k, std::vector<int> list) {
	if (list.empty())
		return 0;

	std::ranges::sort(list);

	int found = 0;
	for (size_t i = 0, j = list.size() - 1; i < j;) {
		int const sum = list[i] + list[j];
		if (sum < k)
			i++;
		else if (sum > k)
			j--;
		else {
			std::cout << " match: " << list[i] << ' ' << list[j] << '\n';
			found += 1;
			i++;
		}
	}

	return found;
}

int main() {
	int const k = 17;
	std::vector const v1{10, 15, 3, 7};
	std::cout << count_k_summed(k, v1) << '\n';

	std::vector<int> test(50);
	std::ranges::generate(test, []() {
		return rand() % 50 - 10;
	});
	std::cout << count_k_summed(k, test) << '\n';

	count_k_summed(10, {});
}
