#include <iostream>
#include <ranges>
#include <string_view>
#include <vector>

int main(int argc, char *argv[]) {
  using namespace std::literals;
  const auto bits = {"https://"sv, "cppreference"sv, "."sv, "com"sv};
  for (char const c : bits | std::views::join) {
    std::cout << c;
  }
  std::endl(std::cout);

  const std::vector<std::vector<int>> v{{1, 2}, {3, 4, 5}, {6}, {7, 8, 9}};
  auto jv = std::ranges::join_view(v);
  for (int const e : jv) {
    std::cout << e << ' ';
  }
  std::endl(std::cout);
  return 0;
}
