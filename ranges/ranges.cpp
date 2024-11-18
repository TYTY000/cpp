#include <iostream>
#include <ranges>
using namespace std;

int main(int argc, char *argv[]) {
  auto const ints = {0, 1, 2, 3, 4, 5};
  auto even = [](int i) { return i % 2 == 0; };
  auto square = [](int i) { return i * i; };
  for (int i : ints | views::filter(even) | views::transform(square)) {
    cout << i << ' ';
  }
  endl(cout);
  return 0;
}
