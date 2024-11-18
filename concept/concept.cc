/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concept.cc                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TYTY000 <767280080@qq.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 13:02:58 by TYTY000           #+#    #+#             */
/*   Updated: 2024/04/30 13:35:20 by TYTY000          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <string>
template <class T>
concept number = requires(T a, T b) {
  a + b;
  a - b;
  a *b;
  a / b;
};

/* Examples of complete sets are
 *
 *      Arithmetic: +, -, *, /, +=, -=, *=, /=
 *      Comparable: <, >, <=, >=, ==, !=
 */

template <number N> auto algo(const N &a, const N &b) { return a / b; }

#include <iostream>
int main(int argc, char *argv[]) {
  int a = algo(5, 6);
  std::cout << a << std::endl;
  std::string xx = "7";
  std::string yy = "9";
  // auto zz = algo(xx, yy); // error: std::string is not a Number
  return 0;
}
