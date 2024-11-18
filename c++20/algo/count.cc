/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count.cc                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jiang <767280080@qq.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:57:21 by Jiang             #+#    #+#             */
/*   Updated: 2024/04/17 11:57:21 by Jiang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  std::vector<int> v{1, 2, 3, 4, 4, 3, 7, 8, 9, 10};

  namespace ranges = std::ranges;

  // 确定 std::vector 中有多少整数匹配目标值。
  int target1 = 3;
  int target2 = 5;
  int num_items1 = ranges::count(v.begin(), v.end(), target1);
  int num_items2 = ranges::count(v, target2);
  std::cout << "number: " << target1 << " count: " << num_items1 << '\n';
  std::cout << "number: " << target2 << " count: " << num_items2 << '\n';

  // 用 lambda 表达式计数被 3 整除的元素。
  int num_items3 =
      ranges::count_if(v.begin(), v.end(), [](int i) { return i % 3 == 0; });
  std::cout << "number divisible by three: " << num_items3 << '\n';

  // 用 lambda 表达式计数被 11 整除的元素。
  int num_items11 = ranges::count_if(v, [](int i) { return i % 11 == 0; });
  std::cout << "number divisible by eleven: " << num_items11 << '\n';
}
