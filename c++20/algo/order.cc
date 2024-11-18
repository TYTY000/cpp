/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   order.cc                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jiang <767280080@qq.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 08:26:25 by Jiang             #+#    #+#             */
/*   Updated: 2024/04/18 09:31:21 by Jiang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <numeric>
#include <ostream>
#include <random>
#include <string>
#include <vector>
struct S {
  int value{0};
  bool specified_state{true};

  S(int v = 0) : value{v} {}
  S(S const &rhs) = default;
  S(S &&rhs) { *this = std::move(rhs); }
  S &operator=(S const &rhs) = default;
  S &operator=(S &&rhs) {
    if (this != &rhs) {
      value = rhs.value;
      specified_state = rhs.specified_state;
      rhs.specified_state = false;
    }
    return *this;
  }
};

template <typename T>
std::ostream &operator<<(std::ostream &os, std::vector<T> const &v) {
  for (const auto &s : v) {
    if constexpr (std::is_same_v<T, S>)
      s.specified_state ? os << s.value << ' ' : os << ". ";
    else if constexpr (std::is_same_v<T, std::string>)
      os << (s.empty() ? "." : s) << ' ';
    else
      os << s << ' ';
  }
  return os;
}

int main() {
  std::string s{"ABCDEF"};
  std::cout << s << " → ";
  std::ranges::reverse(s.begin(), s.end());
  std::cout << s << " → ";
  std::ranges::reverse(s);
  std::cout << s << " │ ";

  std::array a{1, 2, 3, 4, 5};
  for (auto e : a)
    std::cout << e << ' ';
  std::cout << "→ ";
  std::ranges::reverse(a);
  for (auto e : a)
    std::cout << e << ' ';
  std::cout << '\n';

  std::string b(s.size(), ' ');
  std::ranges::reverse_copy(s, b.begin());
  for (auto e : b)
    std::cout << e << ' ';
  std::cout << '\n';
  std::string c(26, ' ');
  std::iota(c.begin(), c.end(), 'A');
  for (int k{1}; k != 5; ++k) {
    std::ranges::rotate(c, c.begin() + k);
    std::cout << "向左旋转 (" << k << "): " << c << '\n';
  }
  for (int k{1}; k != 5; ++k) {
    std::ranges::rotate(c, c.end() - k);
    std::cout << "向右旋转 (" << k << "): " << c << '\n';
  }
  s = {'2', '4', '2', '0', '5', '9', '7', '3', '7', '1'};

  for (auto i = s.begin(); i != s.end(); ++i) {
    std::cout << "i = " << std::ranges::distance(s.begin(), i) << ": ";
    std::ranges::rotate(
        std::ranges::upper_bound(s.begin(), i, *i) // 大于*i的元素
        ,
        i, i + 1); // 都向右移动1
    std::cout << s << '\n';
  }
  std::cout << (std::ranges::is_sorted(s) ? "已排序!" : "未排序.") << '\n';

  std::string d(26, ' ');
  auto pivot = std::find(c.begin(), c.end(), 'N');
  std::ranges::rotate_copy(c, pivot, d.begin());
  std::cout << c << std::endl;
  std::cout << d << std::endl;

  // 如果对于非字符串的平凡值，移动操作应该保留原位置的数值。平凡值类型的移动操作不会产生任何副作用，因此在移动之后，原位置的值应该保持不变。
  // 对于非平凡值类型，移动操作可能会产生副作用，因此在进行移动操作时，通常会将原位置的内容设置为默认初始化的状态，这样可以确保移动后的目标位置的值是有效的。
  // 超出范围则没有结果。

  std::cout << std::left;

  std::vector<S> sa{1, 2, 3, 4, 5, 6, 7};
  std::vector<int> sb{1, 2, 3, 4, 5, 6, 7};
  std::vector<std::string> sc{"α", "β", "γ", "δ", "ε", "ζ", "η"};

  std::cout << "vector<S> \tvector<int> \tvector<string>\n";
  std::cout << sa << "  " << sb << "  " << sc << '\n';

  // 似乎g++ 13.2还不支持ranges::shift_left/right
  std::shift_left(begin(sa), end(sa), 3);
  std::shift_left(begin(sb), end(sb), 3);
  std::shift_left(begin(sc), end(sc), 3);
  std::cout << sa << "  " << sb << "  " << sc << '\n';

  std::shift_right(begin(sa), end(sa), 2);
  std::shift_right(begin(sb), end(sb), 2);
  std::shift_right(begin(sc), end(sc), 2);
  std::cout << sa << "  " << sb << "  " << sc << '\n';

  std::shift_left(begin(sa), end(sa), 8); // 无效果：n >= last - first
  std::shift_left(begin(sb), end(sb), 8); // 同上
  std::shift_left(begin(sc), end(sc), 8); // 同上
  std::cout << sa << "  " << sb << "  " << sc << '\n';

  std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  std::mt19937 g(std::random_device{}());

  // std::shuffle(v.begin(), v.end(), g);
  std::ranges::shuffle(v, g);

  std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
  std::cout << '\n';

  std::string out;
  std::ranges::sample(c, std::back_inserter(out), 5, g);
  std::cout << out << std::endl;
}
