#include <algorithm>
#include <iostream>
#include <type_traits>
using std::cout, std::endl;
template <class... Args, class Ty = std::common_type_t<Args...>>
auto max(Args... args) {
  return std::max({static_cast<Ty>(args)...});
}

int main(int argc, char *argv[]) {
  cout << max(1, 5, 1.2, 'a') << endl;
  return 0;
}
