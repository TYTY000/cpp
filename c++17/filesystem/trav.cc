/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trav.cc                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TYTY000 <767280080@qq.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 15:23:27 by TYTY000           #+#    #+#             */
/*   Updated: 2024/05/07 17:34:47 by TYTY000          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <filesystem>
#include <iostream>

int main(int argc, char *argv[]) {
  auto dir = std::filesystem::current_path().parent_path();
  auto option = std::filesystem::directory_options::skip_permission_denied &
                std::filesystem::directory_options::follow_directory_symlink;
  for (const auto &e :
       std::filesystem::recursive_directory_iterator{dir, option}) {
    // 注意这是个输入迭代器，会在多线程时失效
    // 可以用以下刷新状态：
#if expired
    e.refresh();
    if (e.exists()) {
      .....;
      auto t = e.last_write_time(); // 通常开销很小
    }
#endif
    std::cout << e.path().lexically_normal().string() << '\n';
  }
  // for (std::filesystem::directory_iterator pos{dir};
  //      pos != std::filesystem::directory_iterator{}; ++pos) {
  //   std::cout << pos->path() << '\n';
  // }

  return 0;
}
