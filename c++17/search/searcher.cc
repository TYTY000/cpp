/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   searcher.cc                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TYTY000 <767280080@qq.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 21:34:01 by TYTY000           #+#    #+#             */
/*   Updated: 2024/05/23 21:57:20 by TYTY000          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>
#include <deque>
#include <functional>
#include <iostream>
#include <string>
#include <vector>
class Customer {
  std::string id;

public:
  Customer() = default;
  std::string getID() const { return id; }
  friend bool operator==(const Customer &c1, const Customer &c2) {
    return c1.id == c2.id;
  }
};
int main(int argc, char *argv[]) {
  std::string text{"12312lkdfalsqwjdferjlqwjlerjl"}, sub{"qwj"};
  std::boyer_moore_searcher bmsearch{sub.begin(), sub.end()};
  for (auto [beg, end] = bmsearch(text.begin(), text.end()); beg != text.end();
       std::tie(beg, end) = bmsearch(end, text.end())) {
    std::cout << "found '" << sub << "' at index " << beg - text.begin() << '-'
              << end - text.begin() << '\n';
  }
  // C++17 升级成了泛型搜索器
  std::vector v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::deque q{4, 5, 6};
  auto pos = std::search(v.begin(), v.end(),
                         std::boyer_moore_searcher{q.begin(), q.end()});
  // std::ranges::search(v, std::boyer_moore_searcher{q.begin(), q.end()}); //
  // ranges不支持并行和搜索器

  // 也可以用函数调用运算符
  std::boyer_moore_searcher bm{q.begin(), q.end()};
  auto [beg, end] = bm(v.begin(), v.end());
  if (beg != v.end()) {
    ;
  }

  // 自定义类需要定义判等，搜索器内要传入哈希谓词。
  std::vector<Customer> customers, target;
  std::boyer_moore_searcher bmcus{
      target.begin(), target.end(),
      [](const Customer &c) { return std::hash<std::string>{}(c.getID()); }};
  // 然而，注意搜索器使用谓词时会产生很大的开销，这意味着只有当有非常多的元素并且要搜索的子序列也很大时（例如，在一个
  // 1 千万的顾客集合里搜索一个 1000 个顾客的子序列）才值得这么做。
  // 使用方法同上。
  // 仔细考虑、实际测试。
  return 0;
}
