#include <iostream>
using std::cout, std::endl;
template <class... Args> void f(Args... args) {
  cout << sizeof...(args) << '\n';
}
struct S {
  int a, b;
};

#define F(...) f(0 __VA_OPT__(, ) __VA_ARGS__)
#define G(X, ...) f(0, X __VA_OPT__(, ) __VA_ARGS__)
#define SDEF(sname, ...) S sname __VA_OPT__(= {__VA_ARGS__})

int main(int argc, char *argv[]) {
  int a{}, b{}, c{};
  F(a, b, c);
  F();
  G(a, b, c);
  G(a);
  SDEF(foo);
  SDEF(bar, 1, 2);
  std::cout << bar.a << ' ' << bar.b << endl;
#undef F
  void F();
  F();
  return 0;
}
void F() { cout << "F" << endl; }
