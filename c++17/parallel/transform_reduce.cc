/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_reduce.cc                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TYTY000 <767280080@qq.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 22:27:39 by TYTY000           #+#    #+#             */
/*   Updated: 2024/05/08 22:35:12 by TYTY000          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "timer.h"
#include <execution>
#include <functional>
#include <iostream>
#include <numeric>
#include <vector>

void printSum(long num) {
  std::vector<long> v;
  v.reserve(num * 4);
  for (long i = 0; i < num; ++i) {
    v.insert(v.end(), {1, 2, 3, 4});
  }

  auto sum =
      std::transform_reduce(std::execution::par, v.begin(), v.end(), 0L,
                            std::plus<>{}, [](auto val) { return val * val; });

  std::cout << "transform_reduce(): " << sum << '\n';
}

int main(int argc, char *argv[]) {
  Timer h;
  printSum(1);
  h.printDuration();
  printSum(1e3);
  h.printDuration();
  printSum(1e6);
  h.printDuration();
  printSum(1e8);
  h.printDuration();
  return 0;
}
