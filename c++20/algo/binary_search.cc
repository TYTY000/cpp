/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_search.cc                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jiang <767280080@qq.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:34:56 by Jiang             #+#    #+#             */
/*   Updated: 2024/04/18 17:34:56 by Jiang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>
#include <iostream>
#include <ranges>

int main() {
  constexpr static auto haystack = {1, 3, 4, 5, 9};
  static_assert(std::ranges::is_sorted(haystack));

  for (const int needle : std::views::iota(1) | std::views::take(3)) {
    std::cout << "寻找 " << needle << ": ";
    std::ranges::binary_search(haystack, needle)
        ? std::cout << "找到了 " << needle << '\n'
        : std::cout << "未命中!\n";
  }
}
