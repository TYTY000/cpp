/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   consteval.cc                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TYTY000 <767280080@qq.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 20:57:40 by TYTY000           #+#    #+#             */
/*   Updated: 2024/05/11 21:02:37 by TYTY000          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

constexpr unsigned factorial(unsigned n) {
  return n < 2 ? 1 : n * factorial(n - 1);
}

consteval unsigned combination(unsigned m, unsigned n) {
  return factorial(n) / factorial(m) / factorial(n - m);
}

static_assert(factorial(6) == 720);
static_assert(combination(4, 8) == 70);

int main(int argc, char *argv[]) {
  constexpr unsigned x{factorial(4)};
  [[maybe_unused]]
  unsigned y = factorial(argc);
  // constexpr unsigned z = factorial(argc);
  constexpr unsigned k = combination(2, x);
  return 0;
}
