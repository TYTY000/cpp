#include <algorithm>
#include <cmath>
#include <iostream>
#include <ranges>
#include <vector>

static bool abs_compare(int a, int b) { return (std::abs(a) < std::abs(b)); }

int main(int argc, char *argv[]) {
  std::vector<int> v{1, 3, 5, 6, -8, -14};
  namespace ranges = std::ranges;
  auto result = ranges::min_element(v.begin(), v.end());
  std::cout << "min element at " << ranges::distance(v.begin(), result)
            << std::endl;
  result = ranges::min_element(v, abs_compare);
  std::cout << "min element(abs) at " << ranges::distance(v.begin(), result)
            << std::endl;
  return 0;
}
