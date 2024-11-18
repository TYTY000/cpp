/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.cc                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TYTY000 <767280080@qq.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 15:37:20 by TYTY000           #+#    #+#             */
/*   Updated: 2024/05/05 15:53:52 by TYTY000          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <functional>
#include <iostream>
#include <string>
#include <unordered_set>
class Customer {
public:
  explicit Customer(std::string f, std::string l, int v)
      : first(f), last(l), value(v){};
  Customer(Customer &&) = default;
  Customer(const Customer &) = default;
  Customer &operator=(Customer &&) = default;
  Customer &operator=(const Customer &) = default;
  ~Customer() = default;
  auto getFirstname() const { return first; }
  auto getLastname() const { return last; }
  auto getValue() const { return value; }

private:
  std::string first;
  std::string last;
  int value;
};
template <typename T> void hashCombine(std::size_t &seed, const T &val) {
  seed ^= std::hash<T>()(val) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}
template <typename... Types>
std::size_t combinedHashValue(const Types &...args) {
  std::size_t seed = 0;           // 初 始 化seed
  (..., hashCombine(seed, args)); // 链 式 调 用hashCombine()
  return seed;
}
using namespace std::literals;

auto s = combinedHashValue(std::string{"Hi"}, std::string{"World"}, 42);

Customer customer{"John", "Doe", 100};
struct CustomerHash {
  std::size_t operator()(const Customer &c) const {
    return combinedHashValue(c.getFirstname(), c.getLastname(), c.getValue());
  }
};
std::unordered_set<Customer, CustomerHash> coll;
std::unordered_map<Customer, std::string, CustomerHash> map;

bool operator==(const Customer &a, const Customer &b) {
  return a.getValue() == b.getValue();
}
int main(int argc, char *argv[]) {
  std::cout << s << "\n";
  coll.insert(customer);
  map[customer] = "Preferred Customer";
  // 检查Customer对象是否在unordered_set中
  if (coll.find(customer) != coll.end()) {
    std::cout << "Customer found in set!" << std::endl;
  }
  // 检查Customer对象是否在unordered_map中，并获取其值
  if (map.find(customer) != map.end()) {
    std::cout << "Customer found in map with value: " << map[customer]
              << std::endl;
  }
  return 0;
}
