/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.cc                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jiang <767280080@qq.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:45:37 by Jiang             #+#    #+#             */
/*   Updated: 2024/04/17 12:45:37 by Jiang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>
#include <array>
#include <iostream>

int main() {
  std::cout << std::boolalpha << std::ranges::ends_with("static_cast", "cast")
            << '\n'
            << std::ranges::ends_with("const_cast", "cast") << '\n'
            << std::ranges::ends_with("reinterpret_cast", "cast") << '\n'
            << std::ranges::ends_with("dynamic_cast", "cast") << '\n'
            << std::ranges::ends_with("move", "cast") << '\n'
            << std::ranges::ends_with("move_if_noexcept", "cast") << '\n'
            << std::ranges::ends_with("forward", "cast") << '\n';
  static_assert(
      !std::ranges::ends_with("as_const", "cast") and
      !!std::ranges::ends_with("bit_cast", "cast") and
      !std::ranges::ends_with("to_underlying", "cast") and
      !!std::ranges::ends_with(std::array{1, 2, 3, 4}, std::array{3, 4}) and
      !std::ranges::ends_with(std::array{1, 2, 3, 4}, std::array{4, 5}));
}
