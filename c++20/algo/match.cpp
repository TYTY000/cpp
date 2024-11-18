/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jiang <767280080@qq.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 10:34:43 by Jiang             #+#    #+#             */
/*   Updated: 2024/04/17 10:42:04 by Jiang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

// int main() {
//   std::vector<int> v(10, 2);
//   std::partial_sum(v.cbegin(), v.cend(), v.begin());
//   std::cout << "在这些数字中：";
//   std::copy(v.cbegin(), v.cend(), std::ostream_iterator<int>(std::cout, "
//   ")); std::cout << '\n';

//   if (std::all_of(v.cbegin(), v.cend(), [](int i) { return i % 2 == 0; }))
//     std::cout << "所有数字都是偶数\n";

//   if (std::none_of(v.cbegin(), v.cend(),
//                    std::bind(std::modulus<>(), std::placeholders::_1, 2)))
//     std::cout << "没有任何数字是奇数\n";

//   struct DivisibleBy {
//     const int d;
//     DivisibleBy(int n) : d(n) {}
//     bool operator()(int n) const { return n % d == 0; }
//   };

//   if (std::any_of(v.cbegin(), v.cend(), DivisibleBy(7)))
//     std::cout << "至少有一个数字可以被 7 整除\n";
// }
namespace ranges = std::ranges;

constexpr bool some_of(auto &&r, auto &&pred) // 一些但非全部
{
  return not(ranges::all_of(r, pred) or ranges::none_of(r, pred));
}

constexpr auto w = {1, 2, 3};
static_assert(!some_of(w, [](int x) { return x < 1; }));
static_assert(some_of(w, [](int x) { return x < 2; }));
static_assert(!some_of(w, [](int x) { return x < 4; }));

int main() {
  std::vector<int> v(10, 2);
  std::partial_sum(v.cbegin(), v.cend(), v.begin());
  std::cout << "这些数中: ";
  ranges::copy(v, std::ostream_iterator<int>(std::cout, " "));
  std::cout << '\n';

  if (ranges::all_of(v, [](int i) { return i % 2 == 0; }))
    std::cout << "全部都是偶数\n";

  if (ranges::none_of(v,
                      std::bind(std::modulus<int>(), std::placeholders::_1, 2)))
    std::cout << "没有奇数\n";

  auto DivisibleBy = [](int d) { return [d](int m) { return m % d == 0; }; };

  // if (ranges::any_of(v, DivisibleBy(7)))
  if (ranges::any_of(v, std::bind(std::modulus<int>(), 7, 2)))
    std::cout << "至少一个数可被 7 整除\n";
}
