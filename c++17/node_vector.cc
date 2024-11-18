/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_vector.cc                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TYTY000 <767280080@qq.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 22:33:19 by TYTY000           #+#    #+#             */
/*   Updated: 2024/05/23 22:35:03 by TYTY000          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstddef>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
class Node {
  std::string value;
  std::vector<Node> children;

public:
  Node(std::string s) : value{std::move(s)}, children{} {}
  void add(Node n) { children.push_back(std::move(n)); }

  Node &operator[](std::size_t idx) { return children.at(idx); }
  void print(int indent = 0) const {
    std::cout << std::string(indent, ' ') << value << '\n';
    for (const auto &n : children) {
      n.print(indent + 2);
    }
  }
};

int main(int argc, char *argv[]) {
  Node root{"top"};
  root.add(Node{"elem1"});
  root.add(Node{"elem2"});
  root[0].add(Node{"elem1.1"});
  root.print();
  return 0;
}
