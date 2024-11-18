/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equal_range.cc                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jiang <767280080@qq.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:09:27 by Jiang             #+#    #+#             */
/*   Updated: 2024/04/18 17:22:09 by Jiang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>
#include <compare>
#include <iostream>
#include <vector>

struct S {
  int number{};
  char name{};
  // 注：这些比较运算符忽略 name
  friend bool operator==(const S s1, const S s2) {
    return s1.number == s2.number;
  }
  friend auto operator<=>(const S s1, const S s2) {
    return s1.number <=> s2.number;
  }
  friend std::ostream &operator<<(std::ostream &os, S o) {
    return os << '{' << o.number << ", '" << o.name << "'}";
  }
};

void println(auto rem, auto const &v) {
  for (std::cout << rem; auto const &e : v)
    std::cout << e << ' ';
  std::cout << '\n';
}

int main() {
  // 注：非有序，仅按照如下定义的 S 划分
  std::vector<S> vec{{1, 'A'}, {2, 'B'}, {2, 'C'}, {2, 'D'},
                     {4, 'D'}, {4, 'G'}, {3, 'F'}};

  const S value{2, '?'};

  namespace ranges = std::ranges;

  auto a = ranges::equal_range(vec, value);
  println("1. ", a);

  auto b = ranges::equal_range(vec, 'D', {}, &S::name);
  println("2. ", b);

  auto c = ranges::equal_range(vec, 'D', ranges::greater{}, &S::name);
  println("3. ", c);

  auto d = ranges::equal_range(vec.begin(), vec.end(), 'D', ranges::less{},
                               &S::name);
  println("4. ", d);
}
