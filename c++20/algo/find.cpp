/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jiang <767280080@qq.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 10:55:36 by Jiang             #+#    #+#             */
/*   Updated: 2024/04/17 11:03:02 by Jiang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <algorithm>
#include <forward_list>
#include <iomanip>
#include <iostream>
#include <string_view>

// C++23
int main() {
  constexpr static auto v = {1, 2, 3, 1, 2, 3, 1, 2};
  {
    constexpr auto i1 = std::ranges::find_last(v.begin(), v.end(), 3);
    constexpr auto i2 = std::ranges::find_last(v, 3);
    static_assert(std::ranges::distance(v.begin(), i1.begin()) == 5);
    static_assert(std::ranges::distance(v.begin(), i2.begin()) == 5);
  }
  {
    constexpr auto i1 = std::ranges::find_last(v.begin(), v.end(), -3);
    constexpr auto i2 = std::ranges::find_last(v, -3);
    static_assert(i1.begin() == v.end());
    static_assert(i2.begin() == v.end());
  }

  auto abs = [](int x) { return x < 0 ? -x : x; };

  {
    auto pred = [](int x) { return x == 3; };
    constexpr auto i1 =
        std::ranges::find_last_if(v.begin(), v.end(), pred, abs);
    constexpr auto i2 = std::ranges::find_last_if(v, pred, abs);
    static_assert(std::ranges::distance(v.begin(), i1.begin()) == 5);
    static_assert(std::ranges::distance(v.begin(), i2.begin()) == 5);
  }
  {
    auto pred = [](int x) { return x == -3; };
    constexpr auto i1 =
        std::ranges::find_last_if(v.begin(), v.end(), pred, abs);
    constexpr auto i2 = std::ranges::find_last_if(v, pred, abs);
    static_assert(i1.begin() == v.end());
    static_assert(i2.begin() == v.end());
  }

  {
    auto pred = [](int x) { return x == 1 or x == 2; };
    constexpr auto i1 =
        std::ranges::find_last_if_not(v.begin(), v.end(), pred, abs);
    constexpr auto i2 = std::ranges::find_last_if_not(v, pred, abs);
    static_assert(std::ranges::distance(v.begin(), i1.begin()) == 5);
    static_assert(std::ranges::distance(v.begin(), i2.begin()) == 5);
  }
  {
    auto pred = [](int x) { return x == 1 or x == 2 or x == 3; };
    constexpr auto i1 =
        std::ranges::find_last_if_not(v.begin(), v.end(), pred, abs);
    constexpr auto i2 = std::ranges::find_last_if_not(v, pred, abs);
    static_assert(i1.begin() == v.end());
    static_assert(i2.begin() == v.end());
  }

  using P = std::pair<std::string_view, int>;
  std::forward_list<P> list{
      {"one", 1}, {"two", 2}, {"three", 3},
      {"one", 4}, {"two", 5}, {"three", 6},
  };
  auto cmp_one = [](const std::string_view &s) { return s == "one"; };

  // 寻找满足比较器的最后一个元素，其按 pair::first 投影
  const auto subrange = std::ranges::find_last_if(list, cmp_one, &P::first);

  // 打印所找到的元素和其后的“尾部”
  for (P const &e : subrange)
    std::cout << '{' << std::quoted(e.first) << ", " << e.second << "} ";
  std::cout << '\n';
}
// #include <algorithm>
// #include <format>
// #include <iostream>
// #include <iterator>
// #include <string>
// #include <vector>

// void projector_example() {
//   struct folk_info {
//     unsigned uid;
//     std::string name, position;
//   };

//   std::vector<folk_info> folks{
//       {0, "Ana", "dev"}, {1, "Bob", "devops"}, {2, "Eve", "ops"}};

//   auto it = std::ranges::find(folks, "Eve", &folk_info::name);
//   std::cout << std::format("Eve 的信息:\n"
//                            "    uid: {}\n"
//                            "    名字: {}\n"
//                            "    职位: {}\n\n",
//                            it->uid, it->name, it->position);
// }

// int main() {
//   namespace ranges = std::ranges;

//   projector_example();

//   const int n1 = 3;
//   const int n2 = 5;
//   const auto v = {4, 1, 3, 2};

//   if (ranges::find(v, n1) != v.end())
//     std::cout << "v 包含: " << n1 << '\n';
//   else
//     std::cout << "v 不包含: " << n1 << '\n';

//   if (ranges::find(v.begin(), v.end(), n2) != v.end())
//     std::cout << "v 包含: " << n2 << '\n';
//   else
//     std::cout << "v 不包含: " << n2 << '\n';

//   auto is_even = [](int x) { return x % 2 == 0; };

//   if (auto result = ranges::find_if(v.begin(), v.end(), is_even);
//       result != v.end())
//     std::cout << "v 中的第一个偶数元素: " << *result << '\n';
//   else
//     std::cout << "v 中没有偶数元素n";

//   if (auto result = ranges::find_if_not(v, is_even); result != v.end())
//     std::cout << "v 中的第一个奇数元素: " << *result << '\n';
//   else
//     std::cout << "v 中没有奇数元素\n";

//   auto divides_13 = [](int x) { return x % 13 == 0; };

//   if (auto result = ranges::find_if(v, divides_13); result != v.end())
//     std::cout << "v 中的第一个可被 13 整除的元素: " << *result << '\n';
//   else
//     std::cout << "v 中没有可被 13 整除的元素\n";

//   if (auto result = ranges::find_if_not(v.begin(), v.end(), divides_13);
//       result != v.end())
//     std::cout << "v 中的第一个不可被 13 整除元素: " << *result << '\n';
//   else
//     std::cout << "v 中没有不可被 13 整除的元素\n";
// }
// #include <algorithm>
// #include <array>
// #include <iostream>

// int main() {
//   const auto v = {1, 2, 3, 4};

//   for (const int n : {3, 5})
//     (std::find(v.begin(), v.end(), n) == std::end(v))
//         ? std::cout << "v 不包含 " << n << '\n'
//         : std::cout << "v 包含 " << n << '\n';

//   auto is_even = [](int i) { return i % 2 == 0; };

//   for (auto const &w : {std::array{3, 1, 4}, {1, 3, 5}})
//     if (auto it = std::find_if(begin(w), end(w), is_even); it != std::end(w))
//       std::cout << "w 包含偶数：" << *it << '\n';
//     else
//       std::cout << "w 不包含偶数\n";
// }
