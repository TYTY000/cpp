/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   container_extract.cc                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TYTY000 <767280080@qq.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 22:22:51 by TYTY000           #+#    #+#             */
/*   Updated: 2024/05/23 22:28:21 by TYTY000          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <map>
#include <string>
#include <utility>
void print_map(std::map<int, std::string> m) {
  for (const auto &[k, v] : m) {
    std::cout << "k: " << k << "\t v: " << v << "\n";
  }
}

template <typename T1, typename T2>
void print(const T1 &coll1, const T2 &coll2) {
  std::cout << "values:\n";
  for (const auto &[key, value] : coll1) {
    std::cout << " [" << key << ":" << value << "]";
  }
  std::cout << '\n';
  for (const auto &[key, value] : coll2) {
    std::cout << " [" << key << ":" << value << "]";
  }
  std::cout << '\n';
}

int main(int argc, char *argv[]) {
  std::map<int, std::string> m{
      {1, "mango"},
      {2, "papaya"},
      {3, "guava"},
  };

  print_map(m);
  auto nh = m.extract(2); // nh的类型为decltype(m)::node_type
  nh.key() = 5;
  m.insert(std::move(nh));
  print_map(m);

  std::cout << std::endl;
  std::multimap<double, std::string> src{
      {1.1, "one"}, {2.2, "two"}, {3.3, "three"}};
  std::map<double, std::string> dst{{3.3, "old data"}};
  print(src, dst);
  // 把 一 些 元 素 从multimap src中 移 动 到map dst 中：
  dst.insert(src.extract(src.find(1.1))); // 使 用 迭 代 器 移 动
  dst.insert(src.extract(2.2));           // 使 用key移 动
  print(src, dst);
  auto [pos, done, node] = dst.insert(src.extract(3.3));
  if (!done) {
    std::cout << "insert() of node handle failed:" << " tried to insert key '"
              << node.key() << "' with value '" << node.mapped()
              << "' but key exists with value '" << pos->second << "'\n";
  }
  // node会自动析构，不会泄露！
  return 0;
}
