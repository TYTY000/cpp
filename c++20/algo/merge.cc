/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge.cc                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jiang <767280080@qq.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 18:02:36 by Jiang             #+#    #+#             */
/*   Updated: 2024/04/18 18:28:18 by Jiang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <random>
#include <ranges>
#include <vector>

template <std::random_access_iterator I, std::sentinel_for<I> S>
  requires std::sortable<I>
void merge_sort(I first, S last) {
  if (last - first > 1) {
    I middle{first + (last - first) / 2};
    merge_sort(first, middle);
    merge_sort(middle, last);
    std::ranges::inplace_merge(first, middle, last);
  }
}

int main(int argc, char *argv[]) {
  std::mt19937 gen(std::random_device{}());
  std::uniform_int_distribution<> dis(0, 9);

  std::vector<int> v1(10), v2(10);
  std::ranges::generate(v1, std::bind(dis, std::ref(gen)));
  std::ranges::generate(v2, std::bind(dis, std::ref(gen)));
  std::ranges::copy(v1, std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;
  std::ranges::copy(v2, std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;

  std::ranges::sort(v1);
  std::ranges::sort(v2);
  std::ranges::copy(v1, std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;
  std::ranges::copy(v2, std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;

  std::vector<int> out;
  std::ranges::merge(v1, v2, std::back_inserter(out));

  std::ranges::copy(out.cbegin(), out.cend(),
                    std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;

  std::vector<int> v(10);
  std::ranges::generate(v, std::bind(dis, std::ref(gen)));
  std::ranges::copy(v, std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;
  merge_sort(v.begin(), v.end());
  std::ranges::copy(v, std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;
  return 0;
}
