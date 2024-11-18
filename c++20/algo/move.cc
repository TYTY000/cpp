/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.cc                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jiang <767280080@qq.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:00:26 by Jiang             #+#    #+#             */
/*   Updated: 2024/04/17 15:04:50 by Jiang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>
#include <chrono>
#include <iostream>
#include <iterator>
#include <list>
#include <thread>
#include <vector>

void f(int n) {
  std::this_thread::sleep_for(std::chrono::seconds(n));
  std::cout << "线程 " << n << " 终止" << std::endl;
}

int main() {
  std::vector<std::jthread> v;
  v.emplace_back(f, 1);
  v.emplace_back(f, 2);
  v.emplace_back(f, 3);
  std::list<std::jthread> l;

  // copy() 无法编译，因为 std::jthread 不可复制
  // std::move(v.begin(), v.end(), std::back_inserter(l));
  std::ranges::move(v, std::back_inserter(l));
  // for thread
  // for (auto &t : l) {
  //   t.join();
  // }
}
