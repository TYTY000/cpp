/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate.cc                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jiang <767280080@qq.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:28:48 by Jiang             #+#    #+#             */
/*   Updated: 2024/04/17 17:33:35 by Jiang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <random>
#include <vector>
int main(int argc, char *argv[]) {
  // std::vector<int> v(10);
  // std::generate(v.begin(), v.end(), [n = 0]() mutable { return ++n; });
  // std::ranges::generate(v, [n = 0]() mutable { return ++n; });
  // std::ranges::generate_n(v.begin(), 5, [n = 0]() mutable { return ++n; });
  // std::ranges::copy(v, std::ostream_iterator<int>(std::cout, " "));
  std::mt19937 rand;
  std::generate_n(
      std::ostream_iterator<std::mt19937::result_type>(std::cout, " "), 10,
      std::ref(rand));
  return 0;
}
