/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TYTY000 <767280080@qq.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 19:46:49 by TYTY000           #+#    #+#             */
/*   Updated: 2024/05/07 20:19:01 by TYTY000          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "timer.h"
#include <algorithm>
#include <execution>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

auto compare_substr = [](const auto &a, const auto &b) {
  return a.substr(2) < b.substr(2);
};

auto compare_sv_substr = [](const auto &a, const auto &b) {
  return std::string_view{a}.substr(2) < std::string_view{b}.substr(2);
};

void sort_print(const auto &v, Timer &t, auto compare_func) {
  for (int i = 0; i < 2; i++) {
    auto v2{v};
    auto v3{v};
    auto v4{v};
    std::ranges::sort(v4, compare_func);
    t.printDuration();
    std::sort(std::execution::par, v2.begin(), v2.end(), compare_func);
    t.printDuration();
    std::sort(std::execution::par_unseq, v3.begin(), v3.end(), compare_func);
    t.printDuration();
    std::cout
        << "===========================================================\n";
  }
}

int main(int argc, char *argv[]) {
  std::vector<std::string> v;
  int num = 1e6;
  for (int i = 0; i < num / 2; ++i) {
    v.emplace_back("id" + std::to_string(i));
    v.emplace_back("ID" + std::to_string(i));
  }
  Timer t;

  sort_print(v, t, std::less<>());
  std::cout << '\n';
  // 并行快20多倍，乱序变化不大
  sort_print(v, t, compare_substr);
  std::cout << '\n';
  // 并行快70倍，乱序变化不大
  sort_print(v, t, compare_sv_substr);
  std::cout << '\n';
  // 并行快70倍，乱序变化不大
  // 越复杂的函数 开销越大 并行效果越好
  return 0;
}
