/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_scan.cc                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TYTY000 <767280080@qq.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 12:31:10 by TYTY000           #+#    #+#             */
/*   Updated: 2024/05/09 12:35:21 by TYTY000          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>
#include <array>
#include <functional>
#include <iostream>
#include <iterator>
#include <numeric>
int main(int argc, char *argv[]) {
  std::array a{1, 2, 3, 4, 5, 6, 7, 8, 9};
  auto twice = [](int v) { return v + v; };
  std::cout << "original array:\t";
  std::copy(a.begin(), a.end(), std::ostream_iterator<int>(std::cout, " "));
  std::cout << "\ntransform_inclusive_scan():\t";
  std::transform_inclusive_scan(a.cbegin(), a.cend(),
                                std::ostream_iterator<int>(std::cout, " "),
                                std::plus{}, twice, 0);
  std::cout << "\ntransform_exclusive_scan():\t";
  std::transform_exclusive_scan(a.cbegin(), a.cend(),
                                std::ostream_iterator<int>(std::cout, " "), 100,
                                std::plus{}, twice);
  return 0;
}
