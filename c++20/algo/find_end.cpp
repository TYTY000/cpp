/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_end.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jiang <767280080@qq.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:05:26 by Jiang             #+#    #+#             */
/*   Updated: 2024/04/17 11:09:20 by Jiang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <algorithm>
#include <array>
#include <cctype>
#include <iostream>
#include <ranges>
#include <string_view>

void print(const auto haystack, const auto needle) {
  const auto pos = std::distance(haystack.begin(), needle.begin());
  std::cout << "In \"";
  for (const auto c : haystack)
    std::cout << c;
  std::cout << "\" found \"";
  for (const auto c : needle)
    std::cout << c;
  std::cout << "\" at position [" << pos << ".." << pos + needle.size() << ")\n"
            << std::string(4 + pos, ' ') << std::string(needle.size(), '^')
            << '\n';
}

int main() {
  using namespace std::literals;
  constexpr auto secret{"password password word..."sv};
  constexpr auto wanted{"password"sv};

  constexpr auto found1 = std::ranges::find_end(secret.cbegin(), secret.cend(),
                                                wanted.cbegin(), wanted.cend());
  print(secret, found1);

  constexpr auto found2 = std::ranges::find_end(secret, "word"sv);
  print(secret, found2);

  const auto found3 = std::ranges::find_end(
      secret, "ORD"sv, [](const char x, const char y) { // 用二元谓词
        return std::tolower(x) == std::tolower(y);
      });
  print(secret, found3);

  const auto found4 =
      std::ranges::find_end(secret, "SWORD"sv, {}, {}, [](char c) {
        return std::tolower(c);
      }); // 投影第二范围
  print(secret, found4);

  static_assert(std::ranges::find_end(secret, "PASS"sv).empty()); // => 找不到
}
// #include <algorithm>
// #include <array>
// #include <cmath>
// #include <iostream>

// auto print_result = [](auto result, const auto &v) {
//   result == v.end() ? std::cout << "未找到序列\n"
//                     : std::cout << "最后一次在位置 "
//                                 << std::distance(v.begin(), result)
//                                 << " 出现\n";
// };

// int main() {
//   const auto v = {1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4};

//   for (auto const &x : {std::array{1, 2, 3}, {4, 5, 6}}) {
//     auto iter =
//         std::find_end(v.begin(), v.end(), x.begin(), x.end()); // 重载 (1)
//     print_result(iter, v);
//   }

//   for (auto const &x : {std::array{-1, -2, -3}, {-4, -5, -6}}) {
//     auto iter =
//         std::find_end(v.begin(), v.end(), x.begin(), x.end(), // 重载 (3)
//                       [](int x, int y) { return std::abs(x) == std::abs(y);
//                       });
//     print_result(iter, v);
//   }
// }
