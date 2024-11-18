/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.cc                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jiang <767280080@qq.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:53:32 by Jiang             #+#    #+#             */
/*   Updated: 2024/04/18 17:03:13 by Jiang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>
int main(int argc, char *argv[]) {
  std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::ranges::stable_sort(v, std::greater<>());
  std::ranges::copy(v, std::ostream_iterator<int>(std::cout, " "));
  auto m = v.begin() + v.size() / 2;
  // std::nth_element(v.begin(), m, v.end());
  std::ranges::nth_element(v, v.begin() + v.size() / 2);
  std::cout << "\n中值为 " << v[v.size() / 2] << '\n';
  std::ranges::copy(v, std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;
  assert(std::accumulate(v.begin(), m, 0) < std::accumulate(m, v.end(), 0));
  // std::nth_element(v.begin(), v.begin() + 1, v.end(), std::greater<>());
  std::ranges::nth_element(v, v.begin() + 1, std::greater<int>());
  std::ranges::copy(v, std::ostream_iterator<int>(std::cout, " "));
  return 0;
}
