/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cc                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TYTY000 <767280080@qq.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 20:19:19 by TYTY000           #+#    #+#             */
/*   Updated: 2024/05/23 21:28:10 by TYTY000          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>
#include <execution>
#include <functional>
#include <string>
int main(int argc, char *argv[]) {
  std::string str, sub;
  auto idx = str.find(sub);
  auto pos = std::search(str.begin(), str.end(), sub.begin(), sub.end());
  auto posa = std::ranges::search(str, sub);
  auto posb = std::search(std::execution::par, str.begin(), str.end(),
                          sub.begin(), sub.end());
  auto posc =
      std::search(std::execution::par, str.begin(), str.end(), sub.begin(),
                  sub.end(), std::default_searcher{sub.begin(), sub.end()});
  auto posd =
      std::search(std::execution::par, str.begin(), str.end(), sub.begin(),
                  sub.end(), /* std::boyer_moore_searcher */
                  std::boyer_moore_horspool_searcher{sub.begin(), sub.end()});
  // par并行快，是串行的3倍。
  // 用boyer_moore_searcher快，原理是用预存表。 平均比串行快50~100倍。
  // boyer_moore_horspool_searcher用时间换空间，大部分比串行快3倍。
  // 尽量进行测试。
  return 0;
}
