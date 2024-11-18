/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.cc                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TYTY000 <767280080@qq.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 09:46:53 by TYTY000           #+#    #+#             */
/*   Updated: 2024/05/07 10:21:28 by TYTY000          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <filesystem>
#include <iostream>

void printPath(const std::filesystem::path &p) {
  std::cout << "path elements of \"" << p.string() << "\"\n";
  for (auto e : p) {
    // std::cout << " " << e;
    std::cout << " \"" << e.string() << '"';
  }
}
int main(int argc, char *argv[]) {
  std::filesystem::path p{"/dir/./sub//sub1/../sub2"};
  std::filesystem::path p2{std::filesystem::current_path()};
  std::cout << "path: " << p << '\n';
  std::cout << "string(): " << p.string() << '\n';
  std::wcout << "wstring(): " << p.wstring() << '\n';
  std::cout << "lexically_normal(): " << (p = p.lexically_normal()) << '\n';
  std::cout << "lexically_relative(): " << p.lexically_relative(p2) << '\n';
  std::cout << "lexically_relative(): " << p2.lexically_relative(p) << '\n';
  std::cout << "lexically_proximate(): " << p2.lexically_proximate(p) << '\n';
  std::filesystem::path p3{"/dir\\subdir/subsubdir\\/./\\"};
  std::cout << "p3: " << p << '\n';
  std::cout << "string(): " << p3.string() << '\n';
  std::wcout << "wstring(): " << p3.wstring() << '\n';
  std::cout << "lexically_normal(): " << p3.lexically_normal() << '\n';
  std::cout << "generic_string(): " << p3.generic_string() << '\n';
  std::wcout << "generic_wstring(): " << p3.generic_wstring() << '\n';
  // 因 为 这 是 在Windows 下， 相 应 的 本 地 字 符 串 类 型 是wstring：
  // std::cout << "native(): " << p3.native() << '\n'; // Windows!
  std::wcout << "c_str(): " << p3.c_str() << '\n';
  std::cout << "make_referred(): " << p3.make_preferred() << '\n';
  std::cout << "p3: " << p3 << '\n';
  printPath(p3);

  return 0;
}
