/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unique.cc                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jiang <767280080@qq.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 19:50:25 by Jiang             #+#    #+#             */
/*   Updated: 2024/04/17 21:59:42 by Jiang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <iterator>
#include <list>
#include <ostream>
#include <string>
#include <unordered_set>
#include <vector>
int main(int argc, char *argv[]) {
  // std::vector<int> v{1, 1, 2, 3, 3, 4, 4, 5, 6, 7, 8, 8, 9, 9};
  // const auto [first, last] = std::ranges::unique(v);
  // v.erase(first, last);
  // std::ranges::copy(v, std::ostream_iterator<int>(std::cout, " "));
  std::string str{"The     string   with  many    spaces!"};
  std::string s1;
  std::ranges::unique_copy(str, std::back_inserter(s1), [](char c1, char c2) {
    return c1 == ' ' and c2 == ' ';
  });
  std::ranges::copy(s1, std::ostream_iterator<char>(std::cout));
  std::cout << std::endl;
  std::vector<int> v1 = {-1, 1, -2, 2, -3, 3, 4};
  std::list<int> v2;
  // std::sort(v1.begin(), v1.end(),
  //           [](int a, int b) { return std::abs(a) < std::abs(b); });

  // std::ranges::copy(v1, std::ostream_iterator<int>(std::cout, " "));
  // std::cout << std::endl;
  // std::ranges::unique(v1);
  // std::ranges::sort(v1, std::ranges::greater());
  // std::ranges::copy(v1, std::ostream_iterator<int>(std::cout, " "));
  // std::cout << std::endl;

  // std::ranges::unique_copy(v1, std::back_inserter(v2), [](int a, int b) {
  //   return std::abs(a) == std::abs(b);
  // });
  std::ranges::transform(v1, v1.begin(), [](int i) { return std::abs(i); });
  std::ranges::copy(v1, std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;
  std::unordered_set<int> seen;
  for (int num : v1) {
    if (seen.find(num) != seen.end()) {
      v2.push_back(num);
    } else {
      seen.insert(num);
    }
  }

  std::ranges::copy(v2, std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;
  return 0;
}
