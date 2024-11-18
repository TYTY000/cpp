/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cc                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TYTY000 <767280080@qq.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 20:33:56 by TYTY000           #+#    #+#             */
/*   Updated: 2024/05/06 22:53:47 by TYTY000          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdlib>
#include <filesystem>
#include <iostream>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cout << "Usage: " << argv[0] << " <path>\n";
    return EXIT_FAILURE;
  }

  namespace fs = std::filesystem;

  switch (fs::path p{argv[1]}; fs::status(p).type()) {
  case fs::file_type::regular:
    std::cout << p << " exists with " << fs::file_size(p) << " bytes.\n";
    break;
  case fs::file_type::directory:
    std::cout << p << " is a directory containing\n";
    for (const auto &d : fs::directory_iterator{p}) {
      std::cout << " " << d.path() << "\n";
    }
    break;
  case fs::file_type::not_found:
    std::cout << p << " not exists.\n";
    break;
  default:
    std::cout << p << " is a special file.\n";
    break;
  }

  //   block 	a block special file
  // character 	a character special file
  // fifo 	a FIFO (also known as pipe) file
  // socket 	a socket file
  //   这些都是在Unix或类Unix系统（如Linux）中使用的特殊文件类型，它们主要用于设备和进程间的通信。

  //     块特殊文件（Block Special
  //     File）：块特殊文件充当了块设备的直接接口。块设备是任何以数据块为单位执行数据输入/输出的设备。例如，硬盘设备（/dev/sda）及硬盘分区（/dev/hda1）等。

  //     字符特殊文件（Character Special
  //     File）：字符特殊文件与块设备类似，但数据是一次一个字符（八位或一个字节）地写入。例如，终端文件、NULL文件、文件描述符文件或系统控制台文件。

  //     FIFO文件：FIFO特殊文件（也称为命名管道）类似于管道，除了它是作为文件系统的一部分进行访问的。它可以被多个进程打开进行读写。当进程通过FIFO交换数据时，内核会在不将其写入文件系统的情况下内部传递所有数据。

  //     套接字文件（Socket
  //     File）：套接字是一种特殊文件，用于进程间通信，使两个进程可以交换数据。当数据从套接字文件读取或写入时，请求由该设备的驱动程序处理。

  // 这些特殊文件类型提供了一种通用的硬件设备接口，因为可以使用文件I/O工具来访问设备。这些文件类型的主要区别在于它们如何处理数据和设备如何响应数据请求。希望这个解释对你有所帮助！

  // if (fs::is_regular_file(p)) {
  //   std::cout << p << " exists with " << fs::file_size(p) << " bytes.\n";
  // } else if (fs::is_directory(p)) {
  //   std::cout << p << " is a directory containing\n";
  //   for (const auto &d : fs::directory_iterator{p}) {
  //     std::cout << " " << d.path() << "\n";
  //   }
  // } else if (fs::exists(p)) {
  //   std::cout << p << " is a special file.\n";
  // } else {
  //   std::cout << p << " not exists.\n";
  // }

  return 0;
}
