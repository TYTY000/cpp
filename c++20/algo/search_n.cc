/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_n.cc                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jiang <767280080@qq.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:37:24 by Jiang             #+#    #+#             */
/*   Updated: 2024/04/17 12:39:27 by Jiang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>
#include <iostream>
#include <iterator>

template <class Container, class Size, class T>
constexpr bool consecutive_values(const Container &c, Size count, const T &v) {
  return std::ranges::search_n(c, count, v).end() != std::end(c);
}

int main() {
  constexpr char sequence[] = "1001010100010101001010101";

  static_assert(consecutive_values(sequence, 3, '0'));

  std::cout << std::boolalpha << "有 4 个连续的零："
            << consecutive_values(sequence, 4, '0') << '\n'
            << "有 3 个连续的零：" << consecutive_values(sequence, 3, '0')
            << '\n';
}
