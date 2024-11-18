/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_of.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jiang <767280080@qq.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:37:20 by Jiang             #+#    #+#             */
/*   Updated: 2024/04/17 11:46:00 by Jiang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <algorithm>
#include <iostream>
#include <iterator>

int main() {
  namespace rng = std::ranges;

  constexpr static auto haystack = {1, 2, 3, 4};
  constexpr static auto needles = {0, 3, 4, 3};

  constexpr auto found1 =
      rng::find_first_of(haystack.begin(), haystack.end(), needles.begin(),
                         needles.end()); // old style
  static_assert(std::distance(haystack.begin(), found1) == 2);

  constexpr auto found2 = rng::find_first_of(haystack, needles);
  static_assert(std::distance(haystack.begin(), found2) == 2);

  constexpr static auto negatives = {-6, -3, -4, -3};
  constexpr auto not_found = rng::find_first_of(haystack, negatives);
  static_assert(not_found == haystack.end());

  constexpr auto found3 =
      rng::find_first_of(haystack, negatives, [](int x, int y) {
        return x == -y;
      }); // 使用二元比较器
  static_assert(std::distance(haystack.begin(), found3) == 2);

  struct P {
    int x, y;
  };
  constexpr static auto p1 = {P{1, -1}, P{2, -2}, P{3, -3}, P{4, -4}};
  constexpr static auto p2 = {P{5, -5}, P{6, -3}, P{7, -5}, P{8, -3}};

  // 仅比较 P::y 数据成员，通过投影它们：
  const auto found4 = rng::find_first_of(p1, p2, {}, &P::y, &P::y);
  std::cout << "在位置 " << std::distance(p1.begin(), found4)
            << " 找到首个等价元素 {" << found4->x << ", " << found4->y
            << "}。\n";
}
// #include <algorithm>
// #include <iostream>
// #include <vector>

// auto print_sequence = [](const auto id, const auto &seq, int pos = -1) {
//   std::cout << id << "{ ";
//   for (int i{}; auto const &e : seq) {
//     const bool mark{i == pos};
//     std::cout << (i++ ? ", " : "");
//     std::cout << (mark ? "[ " : "") << e << (mark ? " ]" : "");
//   }
//   std::cout << " }\n";
// };

// int main() {
//   const std::vector<int> v{0, 2, 3, 25, 5};
//   const auto t1 = {19, 10, 4, 3};
//   const auto t2 = {1, 6, 7, 9};

//   auto find_any_of = [](const auto &v, const auto &t) {
//     const auto result =
//         std::find_first_of(v.begin(), v.end(), t.begin(), t.end());
//     if (result == v.end()) {
//       std::cout << "v 和 t 中没有相等的元素\n";
//       print_sequence("t = ", t);
//       print_sequence("v = ", v);
//     } else {
//       const auto pos = std::distance(v.begin(), result);
//       std::cout << "在位置 " << pos << " 找到匹配 (" << *result << ")\n";
//       print_sequence("t = ", t);
//       print_sequence("v = ", v, pos);
//     }
//   };

//   find_any_of(v, t1);
//   find_any_of(v, t2);
// }
