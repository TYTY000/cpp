#include <functional>
#include <iostream>
#include <utility>

template <auto Func, class... Args>
constexpr auto F_ =
    [](Args... args) { return Func(std::forward<Args>(args)...); };

auto add(int a, int b) { return a + b; }

template <class F, typename... Ts> auto concat(F t, Ts... ts) {
  if constexpr (sizeof...(ts) > 0) {
    return [=](auto... paras) { return t(concat(ts...)(paras...)); };
  } else {
    return [=](auto... paras) { return t(paras...); };
  }
}

int main(int argc, char *argv[]) {
  std::cout << F_<add, int, int>(4, 5);
  auto ret = concat([](int a) { std::cout << a << '\n'; },
                    [](int a) {
                      std::cout << a << '\n';
                      return a;
                    });
  ret(10);
  return 0;
}
