/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.cc                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jiang <767280080@qq.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:41:44 by Jiang             #+#    #+#             */
/*   Updated: 2024/04/17 12:44:50 by Jiang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <algorithm>
// #include <ranges>

// int main(int argc, char *argv[]) {
//   using namespace std::literals;
//   constexpr auto s = "I am eeeeeeeeeeeemporptor";
//   static_assert(std::ranges::starts_with("const_cast", "const"sv));
//   static_assert(std::ranges::starts_with(s, "I am"sv));
//   return 0;
// }
#include <algorithm>
#include <iostream>
#include <ranges>
#include <string_view>

int main() {
  using namespace std::literals;

  constexpr auto ascii_upper = [](char8_t c) {
    return u8'a' <= c && c <= u8'z' ? static_cast<char8_t>(c + u8'A' - u8'a')
                                    : c;
  };

  constexpr auto cmp_ignore_case = [=](char8_t x, char8_t y) {
    return ascii_upper(x) == ascii_upper(y);
  };

  static_assert(std::ranges::starts_with("const_cast", "const"sv));
  static_assert(std::ranges::starts_with("constexpr", "const"sv));
  static_assert(!std::ranges::starts_with("volatile", "const"sv));

  std::cout << std::boolalpha
            << std::ranges::starts_with(u8"Constantinopolis", u8"constant"sv,
                                        {}, ascii_upper, ascii_upper)
            << ' '
            << std::ranges::starts_with(u8"Istanbul", u8"constant"sv, {},
                                        ascii_upper, ascii_upper)
            << ' '
            << std::ranges::starts_with(u8"Metropolis", u8"metro"sv,
                                        cmp_ignore_case)
            << ' '
            << std::ranges::starts_with(u8"Acropolis", u8"metro"sv,
                                        cmp_ignore_case)
            << '\n';

  constexpr static auto v = {1, 3, 5, 7, 9};
  constexpr auto odd = [](int x) { return x % 2; };
  static_assert(std::ranges::starts_with(
      v, std::views::iota(1) | std::views::filter(odd) | std::views::take(3)));
}
