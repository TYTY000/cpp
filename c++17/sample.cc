/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sample.cc                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TYTY000 <767280080@qq.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 22:11:39 by TYTY000           #+#    #+#             */
/*   Updated: 2024/05/23 22:19:21 by TYTY000          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>
#include <iostream>
#include <iterator>
#include <random>
#include <string>
#include <vector>
int main(int argc, char *argv[]) {
  std::vector<std::string> coll;
  for (int i = 0; i < 10000; ++i) {
    coll.push_back("value" + std::to_string(i));
  }
  std::sample(coll.begin(), coll.end(),
              std::ostream_iterator<std::string>(std::cout, "\n"), 10,
              std::mt19937{std::random_device{}()});
  std::ranges::sample(coll, std::ostream_iterator<std::string>{std::cout, "\n"},
                      10, std::default_random_engine{});
  // 只要源区间的迭代器不只是输入迭代器，那么被提取出的子集中元素的顺序将保持稳定。
  return 0;
}
