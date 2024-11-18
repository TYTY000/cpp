/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filetime.cc                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TYTY000 <767280080@qq.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 11:04:44 by TYTY000           #+#    #+#             */
/*   Updated: 2024/05/07 11:19:15 by TYTY000          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <chrono>
#include <filesystem>
#include <format>
#include <iostream>

int main(int argc, char *argv[]) {
  std::filesystem::path p{std::filesystem::current_path()};
  // p /= "filetime.cc";
  p = p.parent_path();
  auto filetime = std::filesystem::last_write_time(p);
  // auto diff = std::filesystem::file_time_type::clock::now() - filetime;
  auto diff = decltype(filetime)::clock::now() - filetime;
  std::cout << p.filename().string() << " is "
            << std::chrono::duration_cast<std::chrono::seconds>(diff).count()
            << " seconds old.\n";
  // C++20
  std::cout << std::format("Final write time is {}", filetime);
  return 0;
}
