#include <cstddef>
#include <iostream>
#include <type_traits>
using namespace std;
#define print(x) cout << #x << " = " << x << '\n'

struct X {
  char c;
  int i;
  double d;
};
struct X1 {
  alignas(16) char c;
  alignas(double) int i;
  double d;
};
struct alignas(16) X2 {
  char c;
  int i;
  double d;
};
struct alignas(16) X3 {
  alignas(8) short c;
  alignas(double) int i;
  double d;
};
struct alignas(4) X4 {
  alignas(8) short c;
  alignas(double) int i;
  double d;
};
int main(int argc, char *argv[]) {
  cout << __alignof__(int) << endl;
  cout << __alignof__(void (*)()) << endl;
  // short x1;
  // __attribute__((aligned(8))) short x2;
  // cout << "x1 = " << __alignof__(x1) << endl;
  // cout << "x2 = " << __alignof__(x2) << endl;
  // auto x3 = alignof(short);
  // auto x4 = alignof(void (*)());
  // print(x3);
  // print(x4);
  print(sizeof(X));
  X x;
  print(sizeof(x.c));
  print(sizeof(x.i));
  print(sizeof(x.d));
  print(sizeof(X1));
  X1 x1;
  print(sizeof(x1.c));
  print(sizeof(x1.i));
  print(sizeof(x1.d));
  print(sizeof(X2));
  X2 x2;
  print(sizeof(x2.c));
  print(sizeof(x2.i));
  print(sizeof(x2.d));
  print(sizeof(X3));
  X3 x3;
  print(sizeof(x3.c));
  print(sizeof(x3.i));
  print(sizeof(x3.d));
  print(sizeof(X4));
  X4 x4;
  print(sizeof(x4.c));
  print(sizeof(x4.i));
  print(sizeof(x4.d));
  cout << std::alignment_of<X4>::value << endl;
  // auto xat = &x3;
  // auto c = &x3.c;
  // auto i = &x3.i;
  // auto d = &x3.d;
  // cout << xat << endl;
  // cout << c << endl;
  // cout << i << endl;
  // cout << d << endl;
  return 0;
}
