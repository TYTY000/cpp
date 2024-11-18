#define showlist(...) puts(#__VA_ARGS__)
#define call(F, ...) F(__VA_ARGS__)
#include <iostream>
int main(int argc, char *argv[]) {
  showlist(1, 2, ***, 189);
  auto ret = call([](int a, int b) { return a + b; }, 10, 100);
  std::cout << ret << '\n';
  return 0;
}
