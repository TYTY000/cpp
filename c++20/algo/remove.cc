/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove.cc                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jiang <767280080@qq.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 19:35:51 by Jiang             #+#    #+#             */
/*   Updated: 2024/04/17 19:48:25 by Jiang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
int main(int argc, char *argv[]) {
  std::vector<int> v{1, 1, 2, 3, 4, 5, 6, 7, 8, 8, 9, 10};
  // inplace , iter of v is still the same
  // const auto removed = std::ranges::remove(v, 1);
  // v.erase(removed.begin(), removed.end());
  // std::ranges::copy(v, std::ostream_iterator<int>(std::cout, " "));

  // const auto [first, last] =
  //     std::ranges::remove_if(v, [](int n) { return n == 1 or n == 8; });
  // v.erase(first, last);
  // std::ranges::copy(v, std::ostream_iterator<int>(std::cout, " "));

  // std::ranges::remove_copy(v, std::ostream_iterator<int>(std::cout, " "), 1);
  std::ranges::remove_copy_if(v, std::ostream_iterator<int>(std::cout, " "),
                              [](int n) { return n == 1 or n == 8; });
  return 0;
}
