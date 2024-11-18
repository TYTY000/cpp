#include <iostream>
struct Empty {};
struct X {
  int i;
  [[no_unique_address]] Empty e;
};
#define print(x) (std::cout << #x << " = " << x << std::endl)
#define LOG(msg, ...)                                                          \
  printf("[" __FILE__ ":%d] " msg "\n", __LINE__ __VA_OPT__(, ) __VA_ARGS__)
int main(int argc, char *argv[]) {
  X x;
  print(sizeof(x));
  print(&(x.i));
  print(&(x.e));
  print(__has_cpp_attribute(deprecated));
  LOG("HELLO");
  LOG("s", 1, 3);
  return 0;
}
