/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_ops.cc                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jiang <767280080@qq.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:37:34 by Jiang             #+#    #+#             */
/*   Updated: 2024/04/18 18:01:30 by Jiang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

void print(const auto &in1, const auto &in2, auto first, auto last) {
  std::cout << "{ ";
  for (const auto &e : in1)
    std::cout << e << ' ';
  std::cout << "}  { ";
  for (const auto &e : in2)
    std::cout << e << ' ';
  std::cout << "} =\n{ ";
  while (!(first == last))
    std::cout << *first++ << ' ';
  std::cout << "}\n\n";
}
void visualize(const auto &v, int min = 1, int max = 10) {
  for (auto i{min}; i <= max; ++i) {
    std::ranges::binary_search(v, i) ? std::cout << i : std::cout << ".";
    std::cout << " ";
  }
  std::cout << "\n";
}
int main() {
  std::vector<int> in1, in2, out;

  in1 = {1, 2, 3, 4, 5};
  in2 = {3, 4, 5, 6, 7};
  out.resize(in1.size() + in2.size());
  const auto ret = std::ranges::set_union(in1, in2, out.begin());
  print(in1, in2, out.begin(), ret.out);

  in1 = {1, 2, 3, 4, 5};
  in2 = {3, 4, 5, 5, 5, 6, 7};
  out.clear();
  out.reserve(in1.size() + in2.size());
  std::ranges::set_union(in2, in1, std::back_inserter(out));
  print(in2, in1, out.cbegin(), out.cend());
  in1 = {1, 2, 2, 3, 4, 5, 6};
  in2 = {2, 2, 3, 3, 5, 7};
  out.clear();
  out.reserve(in1.size() + in2.size());

  std::ranges::set_intersection(in1, in2, std::back_inserter(out));
  print(in1, in2, out.cbegin(), out.cend());

  out.clear();
  out.reserve(in1.size() + in2.size());

  auto [in1_end, in2_end] =
      std::ranges::set_difference(in1, in2, std::back_inserter(out));
  print(in1, in2, out.cbegin(), out.cend());

  auto p = [](const auto &v, std::string_view end = "") {
    std::cout << "{ ";
    for (auto n{v.size()}; auto i : v)
      std::cout << i << (--n ? ", " : " ");
    std::cout << "} " << end;
  };
  p(in1, "\n");
  p(in2, "\n");

  std::vector<int> v1{1, 2, 3, 4, 5, 6, 7, 8};
  std::vector<int> v2{5, 6, 7, 9, 10};
  std::sort(v1.begin(), v1.end());
  std::sort(v2.begin(), v2.end());

  std::vector<int> v_symDifference;

  std::set_symmetric_difference(v1.begin(), v1.end(), v2.begin(), v2.end(),
                                std::back_inserter(v_symDifference));

  visualize(v1);
  visualize(v2);
  visualize(v_symDifference);
}
