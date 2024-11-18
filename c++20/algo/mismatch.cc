/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mismatch.cc                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jiang <767280080@qq.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:02:08 by Jiang             #+#    #+#             */
/*   Updated: 2024/04/17 12:06:41 by Jiang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>
#include <iostream>
#include <ranges>
#include <string>

[[nodiscard]] constexpr std::string mirror_ends(const std::string &in) {
  // return std::string(in.begin(),
  // std::mismatch(in.begin(), in.end(), in.rbegin()).first);
  const auto end = std::ranges::mismatch(in, in | std::views::reverse).in1;
  return {in.cbegin(), end};
}

int main() {
  std::cout << mirror_ends("abXYZba") << '\n'
            << mirror_ends("abca") << '\n'
            << mirror_ends("aba") << '\n';
  using namespace std::literals::string_view_literals;

  static_assert("123"sv == mirror_ends("123!@#321"));
  static_assert("radar"sv == mirror_ends("radar"));
}
