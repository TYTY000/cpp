/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equal.cc                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jiang <767280080@qq.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:07:13 by Jiang             #+#    #+#             */
/*   Updated: 2024/04/17 12:11:06 by Jiang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <ranges>
#include <string_view>
[[nodiscard]]
constexpr bool is_palindrome(const std::string_view &s) {
  // return std::equal(s.cbegin(), s.cbegin() + s.size() / 2, s.crbegin());
  namespace views = std::ranges::views;
  auto half_front = s | views::take(s.size() / 2);
  auto half_rear = s | views::reverse | views::take(s.size() / 2);
  return std::ranges::equal(half_rear, half_front);
}

void test(const std::string_view &s) {
  std::cout << std::quoted(s) << (is_palindrome(s) ? " 是" : " 不是")
            << "回文\n";
}

int main() {
  test("radar");
  test("hello");
  static_assert(is_palindrome("ABBA") and not is_palindrome("AC/DC"));
}
