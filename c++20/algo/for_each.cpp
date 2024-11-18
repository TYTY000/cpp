/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_each.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jiang <767280080@qq.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 10:18:14 by Jiang             #+#    #+#             */
/*   Updated: 2024/04/17 10:18:14 by Jiang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

struct Sum {
  void operator()(int n) { sum += n; }
  int sum{0};
};

int main() {
  std::vector<int> nums{3, 4, 2, 8, 15, 267};

  auto print = [](const auto &n) { std::cout << ' ' << n; };

  namespace ranges = std::ranges;
  std::cout << "before:";
  ranges::for_each(std::as_const(nums), print);
  print('\n');

  ranges::for_each(nums, [](int &n) { ++n; });

  // 对每个数调用 Sum::operator()
  auto [i, s] = ranges::for_each(nums.begin(), nums.end(), Sum());
  assert(i == nums.end());

  std::cout << "after: ";
  ranges::for_each(nums.cbegin(), nums.cend(), print);

  std::cout << "\n"
               "sum: "
            << s.sum << '\n';

  using pair = std::pair<int, std::string>;
  std::vector<pair> pairs{{1, "one"}, {2, "two"}, {3, "three"}};

  std::cout << "project the pair::first: ";
  ranges::for_each(pairs, print, [](const pair &p) { return p.first; });

  std::cout << "\n"
               "project the pair::second:";
  ranges::for_each(pairs, print, &pair::second);
  print('\n');
}
