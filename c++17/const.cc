/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   const.cc                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TYTY000 <767280080@qq.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 22:08:44 by TYTY000           #+#    #+#             */
/*   Updated: 2024/05/23 22:10:48 by TYTY000          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
int main(int argc, char *argv[]) {
  std::vector v{1, 2, 3, 4, 54, 56, 67, 7, 8, 9, 0};
  auto printv = [&v = std::as_const(v)] {
    for (auto e : v) {
      std::cout << e << '\t';
    }
  };
  printv();
  std::cout << std::endl;
  for (int i : {-7, 5, 15, 20}) {
    std::cout << std::clamp(i, 0, 13) << '\n';
  }
  return 0;
}
