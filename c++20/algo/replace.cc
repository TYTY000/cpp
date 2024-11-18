/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.cc                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jiang <767280080@qq.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 17:22:02 by Jiang             #+#    #+#             */
/*   Updated: 2024/04/17 17:27:39 by Jiang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>
#include <iostream>
#include <iterator>
#include <ostream>
#include <vector>
int main(int argc, char *argv[]) {
  std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9};
  // std::ranges::replace_if(v, [](int x) { return x < 5; }, 9);
  // std::ranges::copy(v, std::ostream_iterator<int>(std::cout, " "));
  std::ranges::replace_copy_if(
      v, std::ostream_iterator<int>(std::cout, " "),
      [](int n) { return n < 5; }, 9);
  std::vector<int> f(10);
  std::cout << std::endl;
  // std::ranges::fill(f, 10);
  std::ranges::fill_n(f.begin(), 5, 9);

  std::ranges::copy(f, std::ostream_iterator<int>(std::cout, " "));
  return 0;
}
