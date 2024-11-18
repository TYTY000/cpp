/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fold.cc                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jiang <767280080@qq.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:09:31 by Jiang             #+#    #+#             */
/*   Updated: 2024/04/17 14:24:04 by Jiang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>
#include <functional>
#include <iostream>
#include <ranges>
#include <utility>
#include <vector>
using namespace std;
int main(int argc, char *argv[]) {
  std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8};
  // auto sum = std::ranges::fold_left(v, 0, std::plus<int>());
  auto sum = std::ranges::fold_left_first(v, std::plus<int>());
  cout << "*sum = " << sum.value() << "\n";
  vector<pair<char, float>> data{{'A', 2.f}, {'B', 3.f}, {'C', 3.5f}};
  auto ans =
      ranges::fold_left(data | ranges::views::values, 3.f, std::multiplies<>());

  cout << "ans = " << ans << "\n";
  // string res = ranges::fold_left(
  // v, "A", [](string s, auto x) { return s + " " + to_string(x); });
  string res = ranges::fold_right(
      v, "A", [](auto x, string s) { return s + " " + to_string(x); });

  cout << res << endl;
  return 0;
}
