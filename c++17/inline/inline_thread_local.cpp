/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inline_thread_local.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TYTY000 <767280080@qq.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 09:23:34 by TYTY000           #+#    #+#             */
/*   Updated: 2024/05/05 09:25:11 by TYTY000          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inline_thread_local.hpp"
#include <thread>

void foo();

int main(int argc, char *argv[]) {
  myThreadData.print("main() begin:");
  myThreadData.gName = "thread1 name";
  myThreadData.tName = "thread1 name";
  myThreadData.iName = "thread1 name";
  myThreadData.print("main() later:");
  std::thread t(foo);
  t.join();
  myThreadData.print("main() end:");
  return 0;
}
void foo() {
  myThreadData.print("foo() begin:");
  myThreadData.gName = "thread2 name";
  myThreadData.tName = "thread2 name";
  myThreadData.iName = "thread2 name";
  myThreadData.print("foo() end:");
}
