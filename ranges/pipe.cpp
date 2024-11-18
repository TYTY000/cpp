#include <algorithm>
#include <iostream>
#include <iterator>
#include <ranges>
#include <vector>

template <typename T, class F>
std::vector<T> &operator|(std::vector<T> &v, F f) {
  for (auto &i : v) {
    f(i);
  }
  return v;
}
int main(int argc, char *argv[]) {
  std::vector vec{1, 2, 3, 4, 5, 6};
  vec | [](int i) { std::cout << i << ' '; };
  std::endl(std::cout);
  vec | [](int i) { std::cout << i << ' '; } | [](int &i) { i *= i; };
  std::endl(std::cout);

  std::copy(vec.begin(), vec.end(),
            std::ostream_iterator<int, char>(std::cout, " "));
  return 0;
}
