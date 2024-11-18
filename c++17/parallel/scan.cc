/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan.cc                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TYTY000 <767280080@qq.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 12:20:50 by TYTY000           #+#    #+#             */
/*   Updated: 2024/05/09 12:28:11 by TYTY000          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <array>
#include <iostream>
#include <iterator>
#include <numeric>

int main(int argc, char *argv[]) {
  std::array a1{1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::cout << "default inclusive_scan(): \t";
  std::inclusive_scan(a1.begin(), a1.end(),
                      std::ostream_iterator<int>(std::cout, " "));
  std::cout << "\ndefault exclusive_scan(): \t";
  std::exclusive_scan(a1.begin(), a1.end(),
                      std::ostream_iterator<int>(std::cout, " "), 0);
  std::cout << "\nplus<> inclusive_scan(): \t";
  std::inclusive_scan(a1.begin(), a1.end(),
                      std::ostream_iterator<int>(std::cout, " "), std::plus{},
                      100);
  std::cout << "\nplus<> exclusive_scan(): \t";
  std::exclusive_scan(a1.begin(), a1.end(),
                      std::ostream_iterator<int>(std::cout, " "), 100,
                      std::plus{});
  return 0;
}
