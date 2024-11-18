/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filestatus.cc                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TYTY000 <767280080@qq.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 11:34:40 by TYTY000           #+#    #+#             */
/*   Updated: 2024/05/07 11:42:42 by TYTY000          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <filesystem>
#include <iostream>
#include <string>

std::string asString(const std::filesystem::perms &pm) {
  using perms = std::filesystem::perms;
  std::string s;
  s.resize(9);
  s[0] = (pm & perms::owner_read) != perms::none ? 'r' : '-';
  s[1] = (pm & perms::owner_write) != perms::none ? 'w' : '-';
  s[2] = (pm & perms::owner_exec) != perms::none ? 'x' : '-';
  s[3] = (pm & perms::group_read) != perms::none ? 'r' : '-';
  s[4] = (pm & perms::group_write) != perms::none ? 'w' : '-';
  s[5] = (pm & perms::group_exec) != perms::none ? 'x' : '-';
  s[6] = (pm & perms::others_read) != perms::none ? 'r' : '-';
  s[7] = (pm & perms::others_write) != perms::none ? 'w' : '-';
  s[8] = (pm & perms::others_exec) != perms::none ? 'x' : '-';
  return s;
}

int main(int argc, char *argv[]) {
  std::filesystem::path p{std::filesystem::current_path()};
  p /= "filestatus.cc";
  auto pathStatus{std::filesystem::status(p)};
  std::cout << std::filesystem::is_regular_file(p) << '\n';
  if (pathStatus.type() == std::filesystem::file_type::regular) {
    std::cout << "std::filesystem::file_type::regular" << '\n';
  }
  std::cout << asString(pathStatus.permissions()) << '\n';
  return 0;
}
