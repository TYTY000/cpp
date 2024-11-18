/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memorypool_test.cc                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TYTY000 <767280080@qq.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:40:00 by TYTY000           #+#    #+#             */
/*   Updated: 2024/05/02 16:10:34 by TYTY000          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memorypool.h"
#include <cassert>
#include <iostream>

void stressTest() {
  const int size = 1000000;
  MemoryPool<double> pool;

  // 分配内存
  double **ptrs = new double *[size];
  for (int i = 0; i < size; ++i) {
    ptrs[i] = pool.newElement((double)i);
  }

  // 检查值并释放内存
  for (int i = 0; i < size; ++i) {
    assert(*ptrs[i] == (double)i);
    pool.deleteElement(ptrs[i]);
  }

  delete[] ptrs;
}

int main() {
  stressTest();
  std::cout << "压力测试通过！" << std::endl;
  return 0;
}
