/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cc                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TYTY000 <767280080@qq.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 09:48:08 by TYTY000           #+#    #+#             */
/*   Updated: 2024/05/06 10:08:03 by TYTY000          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdlib>
#include <iostream>
#include <optional>
#include <ostream>
#include <string>
std::optional<int> toInt(const std::string &s) {
  try {
    return std::stoi(s);
  } catch (...) {
    return std::nullopt;
  }
}

#include <complex>
#include <set>
template <typename T>
std::ostream &operator<<(std::ostream &o, std::complex<T> c) {
  return o << c.real() << " " << c.imag();
}
int main(int argc, char *argv[]) {
  for (auto s : {"42", " 088", "hello", "0x33", "44.5"}) {
    std::optional<int> i = toInt(s);
    if (i.has_value()) {
      std::cout << s << "\tto\t" << i.value() << "\n";
    }
  }
  std::optional o6{std::complex{3.0, 4.0}};
  std::cout << o6.value() << std::endl;
  std::optional<std::complex<double>> o7{std::in_place, 5.0, 6.0};
  std::cout << o7.value() << std::endl;

  auto sc = [](int x, int y) { return std::abs(x) < std::abs(y); };
  using namespace std::literals;
  // std::optional<std::set<int, decltype(sc)>> o8{
  // std::in_place, {4, 8, -7, -2, 0, 5}, sc};
  std::optional<std::set<int, decltype(sc)>> o8{
      std::in_place, std::initializer_list<int>{4, 5L}, sc};
  for (auto e : o8.value()) {
    std::cout << e << std::endl;
  }
  return 0;
}
