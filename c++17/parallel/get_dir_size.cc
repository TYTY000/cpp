/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dir_size.cc                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TYTY000 <767280080@qq.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 22:41:45 by TYTY000           #+#    #+#             */
/*   Updated: 2024/05/08 22:45:09 by TYTY000          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <execution>
#include <filesystem>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>
int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cout << "Usage: " << argv[0] << " <path> \n";
    return EXIT_FAILURE;
  }
  std::filesystem::path root{argv[1]};
  std::vector<std::filesystem::path> paths;
  try {
    std::filesystem::recursive_directory_iterator dir{root};
    std::copy(begin(dir), end(dir), std::back_inserter(paths));
  } catch (const std::exception &e) {
    std::cerr << "EXCEPTION: " << e.what() << "\n";
    return EXIT_FAILURE;
  }

  auto sz = std::transform_reduce(
      std::execution::par, std::cbegin(paths), std::cend(paths), uintmax_t{0},
      std::plus<>(), [](const std::filesystem::path &p) {
        return is_regular_file(p) ? file_size(p) : uintmax_t{0};
      });
  std::cout << "size of all" << paths.size() << " regular files: " << sz
            << '\n';
  return 0;
}
