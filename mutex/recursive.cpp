/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TYTY000 <767280080@qq.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 18:18:10 by TYTY000           #+#    #+#             */
/*   Updated: 2024/05/03 18:19:07 by TYTY000          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <mutex>
#include <thread>
std::recursive_mutex mtx;

void recursiveFunction(int count) {
  std::lock_guard<std::recursive_mutex> lc{mtx};
  std::cout << "Locked by thread: " << std::this_thread::get_id()
            << ", count: " << count << std::endl;
  if (count > 0) {
    recursiveFunction(count - 1);
  }
}

int main() {
  std::thread t1(recursiveFunction, 3);
  std::thread t2(recursiveFunction, 2);

  t1.join();
  t2.join();
}
// class X {
//   std::recursive_mutex m;
//   std::string shared;

// public:
//   void func1() {
//     std::lock_guard<std::recursive_mutex> lk(m);
//     shared = "func1";
//     std::cout << "in func1, shared = " << shared << "\n";
//   }

//   void func2() {
//     std::lock_guard<std::recursive_mutex> lk(m);
//     shared = "func2";
//     std::cout << "in func2, shared = " << shared << "\n";
//     func1();
//     std::cout << "back in func2, shared = " << shared << "\n";
//   }
// };

// int main(int argc, char *argv[]) {
//   X x;
//   std::thread t1(&X::func1, &x);
//   std::thread t2(&X::func2, &x);
//   t1.join();
//   t2.join();
//   return 0;
// }
