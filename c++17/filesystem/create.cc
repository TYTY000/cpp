/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.cc                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TYTY000 <767280080@qq.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 22:52:17 by TYTY000           #+#    #+#             */
/*   Updated: 2024/05/07 08:06:42 by TYTY000          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
namespace fs = std::filesystem;
int main(int argc, char *argv[]) {
  try {
    fs::path test_path{"test"};
    std::filesystem::create_directory(test_path);

    auto test_file = test_path / "data.txt";
    std::ofstream data_file{test_file};
    if (!data_file) {
      std::cerr << "Can't open \"" << test_path.string() << "\"\n";
      return EXIT_FAILURE;
    }
    data_file << "The answer is 42\n";
    fs::create_symlink("test", test_path.parent_path() / "slink");
    // 最后，注意这个调用在 Windows
    // 上可能会失败并导致错误处理，因为创建符号链接可能需要管理员权限。
  } catch (const std::filesystem::filesystem_error &e) {
    std::cerr << "EXCEPTION: " << e.what() << "\n";
    std::cerr << " path1: \"" << e.path1().string() << "\"\n";
  }
  std::cout << fs::current_path().string() << ":\n";

  auto iterOpts{fs::directory_options::follow_directory_symlink};
  for (const auto &e : fs::recursive_directory_iterator(".", iterOpts)) {
    std::cout << " " << e.path().lexically_normal().string() << "\n";
  }

  return 0;
}
