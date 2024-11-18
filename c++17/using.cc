/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   using.cc                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TYTY000 <767280080@qq.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 16:36:25 by TYTY000           #+#    #+#             */
/*   Updated: 2024/05/05 16:40:14 by TYTY000          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
template <typename... Ts> struct overload : Ts... {
  using Ts::operator()...;
};

template <typename... Ts> overload(Ts...) -> overload<Ts...>;

auto twice = overload{[](std::string &s) { s += s; }, [](auto &v) { v *= 2; }};

int main(int argc, char *argv[]) {
  int i = 42;
  float f = 4.0;
  std::string s = "hi";
  twice(i), twice(f), twice(s);
  std::cout << i << " " << f << " " << s;
  return 0;
}
