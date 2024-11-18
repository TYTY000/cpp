/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjacent_find.cc                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jiang <767280080@qq.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:48:39 by Jiang             #+#    #+#             */
/*   Updated: 2024/04/17 11:56:12 by Jiang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>
#include <functional>
#include <iostream>
#include <ranges>
#include <vector>

constexpr bool some_of(auto &&r, auto &&pred) {
  return std::ranges::cend(r) !=
         std::ranges::adjacent_find(r, [&pred](auto const &x, auto const &y) {
           return pred(x) != pred(y);
         });
}

constexpr auto a = {0, 0, 0, 0}, b = {1, 1, 1, 1}, c = {1, 1, 0, 0};
auto is_one = [](auto x) { return x == 1; };
static_assert(!some_of(a, is_one) and !some_of(b, is_one) and
              some_of(c, is_one));

int main() {
  std::vector<int> v1{0, 1, 2, 3, 40, 40, 41, 41, 5};

  auto i1 = std::ranges::adjacent_find(v1);

  if (i1 == v1.end())
    std::cout << "没有匹配的相邻元素\n";
  else
    std::cout << "第一对相等的相邻元素位于 " << std::distance(v1.begin(), i1)
              << "，*i1 = " << *i1 << '\n';

  auto i2 = std::ranges::adjacent_find(v1, std::greater<int>());
  if (i2 == v1.end())
    std::cout << "整个 vector 已经是升序的\n";
  else
    std::cout << "非降序子序列中最后的元素位于 "
              << std::distance(v1.begin(), i2) << "，*i2 = " << *i2 << '\n';
}
