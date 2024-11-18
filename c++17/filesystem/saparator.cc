/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   saparator.cc                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TYTY000 <767280080@qq.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 09:39:25 by TYTY000           #+#    #+#             */
/*   Updated: 2024/05/07 09:44:02 by TYTY000          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <filesystem>
#include <iostream>
void printPath(const std::filesystem::path &p) {
  std::cout << "path elements of \"" << p.string() << "\":\n";
  for (std::filesystem::path elem : p) {
    std::cout << " \"" << elem.string() << '"';
  }
  std::cout << '\n';
}
int main() {
  std::filesystem::path p = "/example/path/";
  std::filesystem::path p2{std::filesystem::current_path()};

  // 检查路径是否为空
  if (!p.empty()) {
    // 检查路径是否以分隔符结尾
    if (p.string().back() == std::filesystem::path::preferred_separator) {
      std::cout << p << " has a trailing separator\n";
    } else {
      std::cout << p << " does not have a trailing separator\n";
    }
  }
  if (!p.empty() && (--p.end())->empty()) {
    std::cout << p << " has a trailing separator\n";
  }

  printPath(p2);

  return 0;
}
