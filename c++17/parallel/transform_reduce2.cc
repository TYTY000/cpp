/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_reduce2.cc                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TYTY000 <767280080@qq.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 12:12:06 by TYTY000           #+#    #+#             */
/*   Updated: 2024/05/09 12:18:12 by TYTY000          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <array>
#include <execution>
#include <functional>
#include <iostream>
#include <numeric>

int main(int argc, char *argv[]) {
  std::array a1{3, 2, 1, 5, 6, 7, 4, 8};
  std::array a2{4, 5, 6, 7, 8, 9, 2, 4};
  std::cout << "squared sum: \t"
            << std::transform_reduce(std::execution::par, a1.cbegin(),
                                     a1.cend(), a1.cbegin(), 0L)
            << '\n';
  std::cout << "inner product sum: \t"
            << std::transform_reduce(std::execution::par, a1.cbegin(),
                                     a1.cend(), a2.cbegin(), 0L)
            << '\n';
  std::cout << "MSE :\t"
            << std::transform_reduce(
                   std::execution::par, a1.cbegin(), a1.cend(), a2.cbegin(), 0L,
                   std::plus{},
                   [](auto x, auto y) { return (x - y) * (x - y); })
            << '\n';
  return 0;
}
