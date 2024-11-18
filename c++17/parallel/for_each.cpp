/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_each.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TYTY000 <767280080@qq.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 18:11:29 by TYTY000           #+#    #+#             */
/*   Updated: 2024/05/07 19:44:18 by TYTY000          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "timer.h"
#include <algorithm>
#include <cmath>
#include <execution>
#include <ranges>
#include <vector>

int main(int argc, char *argv[]) {
  int num = 1e7;
  struct Data {
    double value;
    double sqrt;
  };
  std::vector<Data> v;
  v.reserve(num);
  for (int i : std::ranges::views::iota(1, num)) {
    v.push_back(Data(i * 4.44, 0));
  }

  for (int i = 0; i < 5; ++i) {
    Timer t;
    std::for_each(std::execution::par, v.begin(), v.end(),
                  [](auto &val) { val.sqrt = std::sqrt(val.value); });
    t.printDuration("parallel: ");

    std::for_each(std::execution::seq, v.begin(), v.end(),
                  [](auto &val) { val.sqrt = std::sqrt(val.value); });
    t.printDuration("sequential: ");
    // 大约在十倍左右
  }
  // ranges不支持并行版本
  // std::ranges::for_each(v, [](auto &val) { val.sqrt = std::sqrt(val.value);
  // });
  return 0;
}
