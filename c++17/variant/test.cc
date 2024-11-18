/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cc                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TYTY000 <767280080@qq.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 10:27:41 by TYTY000           #+#    #+#             */
/*   Updated: 2024/05/06 12:03:51 by TYTY000          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <boost/core/demangle.hpp>
#include <complex>
#include <iomanip>
#include <iostream>
#include <set>
#include <type_traits>
#include <utility>
#include <variant>
#include <vector>

struct NoDefConstr {
  NoDefConstr(int i) { std::cout << "NoDefConstr::NoDefConstr(int) called\n"; }
};
std::variant<std::monostate, NoDefConstr, int> v2; // OK
                                                   // 理论上讲，
// std::monostate可以作为任意选项，而不是必须作为第一个选项。然而，如果不是第一个选项的话就不能帮助
// variant 进行 默认构造

// 推导指引C++17
template <class... Ts> struct overloaded : Ts... {
  using Ts::operator()...;
};
template <class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

int main(int argc, char *argv[]) {
  std::cout << "index: " << v2.index() << '\n';
  std::variant<int, std::string> var{"hi"}; // 初 始 化 为string选 项
  std::cout << var.index() << '\n';         // 打 印 出1
  var = 42;                                 // 现 在 持 有int选 项
  std::cout << var.index() << '\n';         // 打 印 出0
  try {
    int i = std::get<0>(var); // 通 过 索 引 访 问
    std::string s = std::get<std::string>(
        var); // 通 过 类 型 访 问 （这 里 会 抛 出 异 常 ）
  } catch (
      const std::bad_variant_access &e) { // 当 索 引/类 型 错 误 时 进 行 处 理
    std::cerr << "EXCEPTION: " << e.what() << '\n';
  }
  if (v2.index() == 0) {
    std::cout << "has monostate\n";
  }
  if (!v2.index()) {
    std::cout << "has monostate\n";
  }
  if (std::holds_alternative<std::monostate>(v2)) {
    std::cout << "has monostate\n";
  }
  if (std::get_if<0>(&v2)) {
    std::cout << "has monostate\n";
  }
  if (std::get_if<std::monostate>(&v2)) {
    std::cout << "has monostate\n";
  }
  std::variant<std::complex<double>> v11{
      std::in_place_type<std::complex<double>>, 3.0, 4.0};
  std::variant<std::complex<double>> v12{std::in_place_index<0>, 3.0, 4.0};

  auto sc = [](int x, int y) { return std::abs(x) < std::abs(y); };
  std::variant<std::vector<int>, std::set<int, decltype(sc)>> v15{
      std::in_place_index<1>, {4, 8, -7, -2, 0, 5}, sc};
  std::cout << v15.index() << "\n";
  std::cout << boost::core::demangle(typeid(v15).name()) << "\n";
  std::cout << boost::core::demangle(typeid(std::get<1>(v15)).name()) << "\n";
  std::cout << boost::core::demangle(typeid(std::get_if<1>(&v15)).name())
            << "\n";
  if (nullptr == std::get_if<0>(&v15))
    std::cout << "nullptr";
  else
    std::cout << std::get_if<0>(&v15);
  std::cout << "\n";
  if (auto ip = std::get_if<1>(&v15)) {
    std::cout << boost::core::demangle(typeid(v15).name()) << '\n';
  } else {
    std::cout << "alternative with index 1 not set\n";
  }
  std::variant<int, std::string, double> v16;
  // C++17
  /* template <class... Ts> struct overloaded : Ts... {
   *   using Ts::operator()...;
   * };
   * template <class... Ts> overloaded(Ts...) -> overloaded<Ts...>;
   * v16 = 42;
   */
  // std::visit(
  //     overloaded{[](int &i) { std::cout << "int: " << i << '\n'; },
  //                [](std::string &s) { std::cout << "string: " << s << '\n';
  //                },
  //                [](double &d) { std::cout << "double: " << d << '\n'; }},
  //     v16);

  v16 = 42;
  std::visit([](auto arg) { std::cout << arg << '\n'; }, v16);

  v16 = "hello";
  std::visit([](auto arg) { std::cout << arg << '\n'; }, v16);

  v16 = 42.7;
  std::visit([](auto arg) { std::cout << arg << '\n'; }, v16);

  using var_t = std::variant<int, long, double, std::string>;
  std::vector<var_t> vec = {10, 15l, 1.5, "hello"};
  auto trav_clear = [](auto &&arg) {
    using T = std::decay_t<decltype(arg)>;

    if constexpr (std::is_same_v<T, int>)
      std::cout << "值为 " << arg << " 的 int";
    else if constexpr (std::is_same_v<T, long>)
      std::cout << "值为 " << arg << " 的 long";
    else if constexpr (std::is_same_v<T, double>)
      std::cout << "值为 " << arg << " 的 double";
    else if constexpr (std::is_same_v<T, std::string>)
      std::cout << "值为 " << std::quoted(arg) << " 的 std::string";
    else
      static_assert(false, "探访器无法穷尽类型！");

    arg = std::remove_reference_t<decltype(arg)>{};
    std::cout << " -> ";
    if (std::is_same_v<T, std::string>)
      std::cout << "\"\"";
    else
      std::cout << arg;
    std::cout << '\n';
  };
  for (auto &&v : vec) {

    std::visit([](auto &&arg) { std::cout << arg; }, v);

    var_t w = std::visit([](auto &&arg) -> var_t { return arg + arg; }, v);

    std::cout << "\t翻倍后，变体持有";

    std::visit(trav_clear, w);
  }
  for (auto &&v : vec) {
    // 4. 另一种类型匹配探访器：有三个重载的 operator() 的类
    // 注：此情况下 '(auto arg)' 模板 operator() 将绑定到 'int' 与 'long'，
    //    但它不存在时 '(double arg)' operator() *也会* 绑定到 'int' 与 'long'，
    //    因为两者均可隐式转换到 double。使用此形式时应留心以正确处理隐式转换。
    std::visit(overloaded{
                   [](auto arg) { std::cout << arg << ' '; },
                   [](double arg) { std::cout << std::fixed << arg << ' '; },
                   [](const std::string &arg) {
                     std::cout << std::quoted(arg) << ' ';
                   },
               },
               v);
  }
  return 0;
}
