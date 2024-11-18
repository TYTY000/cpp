/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cc                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TYTY000 <767280080@qq.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 17:35:40 by TYTY000           #+#    #+#             */
/*   Updated: 2024/05/07 17:50:54 by TYTY000          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdint>
#include <iostream>
#include <type_traits>
int main(int argc, char *argv[]) {
  std::cout << std::boolalpha << std::is_swappable_with_v<int, int> << '\n';
  std::cout << std::is_nothrow_swappable_with_v<int, uint32_t> << '\n';
  return 0;
}
