/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.cc                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jiang <767280080@qq.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:11:41 by Jiang             #+#    #+#             */
/*   Updated: 2024/04/17 12:32:11 by Jiang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>
#include <cassert>
#include <functional>
#include <iomanip>
#include <iostream>
#include <string_view>
#include <vector>

using namespace std::literals;

bool contains(const auto &cont, std::string_view s) {
  // 也能使用 str.find()（或从 C++23 起使用 str.contains()）
  // return std::search(cont.begin(), cont.end(), s.begin(), s.end()) !=
  //        cont.end();
  return std::ranges::search(cont, s).end() != cont.end();
  // return cont.find(s) != std::string_view::npos; // 使用 str.find()
  // return cont.contains(s); // 或者从 C++23 起使用 str.contains()
}

int main() {
  // const auto str{"why waste time learning, when ignorance is
  // instantaneous?"sv};
  const auto str{"why waste time learning, when ignorance is instantaneous?"sv};
  assert(contains(str, "learning"));
  assert(not contains(str, "lemming"));

  const std::vector vec(str.begin(), str.end());
  assert(contains(vec, "learning"));
  assert(not contains(vec, "leaning"));

  // 演示 C++17 使用搜索器的重载：
  constexpr auto quote{
      "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed "
      "do eiusmod tempor incididunt ut labore et dolore magna aliqua"sv};

  for (const auto word : {"pisci"sv, "Pisci"sv}) {
    std::cout << "字符串 " << std::quoted(word) << ' ';
    const std::boyer_moore_searcher searcher(word.begin(), word.end());
    const auto it = std::search(quote.begin(), quote.end(), searcher);
    if (it == quote.end())
      std::cout << "未找到\n";
    else
      std::cout << "在偏移 " << it - quote.begin() << " 处找到\n";
  }
  std::string str1 = "Hello, World!";

  // 使用 find()
  size_t found = str1.find("World");
  if (found != std::string::npos)
    std::cout << "'World' found at: " << found << '\n';
  else
    std::cout << "'World' not found\n";

  if (str.contains("World"))
    std::cout << "'World' is in the string\n";
  else
    std::cout << "'World' is not in the string\n";
}
