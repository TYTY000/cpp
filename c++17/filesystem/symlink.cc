/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symlink.cc                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TYTY000 <767280080@qq.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 15:13:53 by TYTY000           #+#    #+#             */
/*   Updated: 2024/05/07 15:21:55 by TYTY000          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <filesystem>
#include <iostream>

int main(int argc, char *argv[]) {
  auto top = std::filesystem::current_path();
  top = absolute(top); // 转 换 为 绝 对 路 径， 用 于 切 换 当 前 目 录
  create_directory(top); // 确 保top存 在
  current_path(top);     // 然 后 切 换 当 前 目 录
  std::cout << std::filesystem::current_path() << '\n'; // 打 印top的 路 径
  // 定 义 我 们 自 己 的 子 目 录 （还 没 有 创 建 ） ：
  std::filesystem::path px{top / "a/x"};
  std::filesystem::path py{top / "a/y"};
  std::filesystem::path ps{top / "a/s"};
  // 打 印 出 一 些 相 对 路 径 （这 些 文 件 还 不 存 在 ） ：
  std::cout << px.relative_path() << '\n'; // 从 当 前 路 径 到px的 相 对 路 径
  std::cout << px.lexically_relative(py) << '\n'; // 从py到px的 路 径： "../x"
  std::cout << relative(px, py) << '\n'; // 从py到px的 路 径： "../x"

  create_directories(px); // 创 建"top/a/x"
  create_directories(py); // 创 建"top/a/y"
  if (!std::filesystem::is_symlink(ps)) {
    std::filesystem::create_symlink(top, ps);
  }
  std::cout << "ps: " << ps << " -> " << std::filesystem::read_symlink(ps)
            << "\n";
  std::cout << px.lexically_relative(ps) << '\n';
  std::cout << relative(px, ps) << '\n';

  auto [cap, _, avail] = std::filesystem::space("/root/");
  std::cout << std::fixed << std::setprecision(2) << avail / 1.0e6 << " of "
            << cap / 1.0e6 << " MB available\n\n";
  return 0;
}
