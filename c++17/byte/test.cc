/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cc                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TYTY000 <767280080@qq.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:20:01 by TYTY000           #+#    #+#             */
/*   Updated: 2024/05/06 17:24:31 by TYTY000          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bitset>
#include <boost/core/demangle.hpp>
#include <cstddef>
#include <iostream>
#include <limits>

int main(int argc, char *argv[]) {
  auto b1 = std::byte{42};
  std::cout << std::numeric_limits<unsigned char>::digits << "\n";
  using ByteBitset = std::bitset<
      std::numeric_limits<std::underlying_type_t<std::byte>>::digits>;
  std::cout << ByteBitset{std::to_integer<unsigned>(b1)} << "\n";
  std::cout << boost::core::demangle(
      typeid(ByteBitset{std::to_integer<unsigned>(b1)}).name());
  std::string s = ByteBitset{std::to_integer<unsigned>(b1)}.to_string();
  std::cout << "\n" << s << "\n";
  return 0;
}
