/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cc                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TYTY000 <767280080@qq.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 12:28:54 by TYTY000           #+#    #+#             */
/*   Updated: 2024/05/13 12:34:04 by TYTY000          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void new_func1(void);

void func1(void) {
  printf("\n Inside func1 \n");
  auto i = 0;

  for (; i < 0xffffffff; i++)
    ;
  new_func1();

  return;
}

static void func2(void) {
  printf("\n Inside func2 \n");
  auto i = 0;

  for (; i < 0xffffffaa; i++)
    ;
  return;
}

int main(void) {
  printf("\n Inside main()\n");
  int i = 0;

  for (; i < 0xffffff; i++)
    ;
  func1();
  func2();

  return 0;
}
