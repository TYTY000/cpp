/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cc                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TYTY000 <767280080@qq.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 14:51:53 by TYTY000           #+#    #+#             */
/*   Updated: 2024/05/05 14:55:15 by TYTY000          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
template <typename T> std::string asString(T x) {
  if constexpr (std::is_same_v<T, std::string>) {
    return x; // 如 果T不 能 自 动 转 换 为string该 语 句 将 无 效
  } else if constexpr (std::is_arithmetic_v<T>) {
    return std::to_string(x); // 如 果T不 是 数 字 类 型 该 语 句 将 无 效
  } else {
    return std::string(x); // 如 果 不 能 转 换 为string该 语 句 将 无 效
  }
}
#include <iostream>

int main(int argc, char *argv[]) {
  {
    std::cout << asString(42) << '\n';
    std::cout << asString(std::string("hello")) << '\n';
    std::cout << asString("hello") << '\n';
  }
  return 0;
}
