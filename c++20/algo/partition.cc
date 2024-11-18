/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   partition.cc                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jiang <767280080@qq.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:43:50 by Jiang             #+#    #+#             */
/*   Updated: 2024/04/18 15:43:26 by Jiang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>
#include <array>
#include <forward_list>
#include <functional>
#include <ios>
#include <iostream>
#include <iterator>
#include <ranges>
namespace rng = std::ranges;

template <std::permutable I, std::sentinel_for<I> S>
constexpr void stable_sort(I first, S last) {
  if (first == last)
    return;

  auto pivot = *rng::next(first, rng::distance(first, last) / 2, last);
  auto left = [pivot](const auto &em) { return em < pivot; };
  auto tail1 = rng::stable_partition(first, last, left);
  auto right = [pivot](const auto &em) { return !(pivot < em); };
  auto tail2 = rng::stable_partition(tail1, right);

  stable_sort(first, tail1.begin());
  stable_sort(tail2.begin(), tail2.end());
}

void print(const auto rem, auto first, auto last, bool end = true) {
  std::cout << rem;
  for (; first != last; ++first)
    std::cout << *first << ' ';
  std::cout << (end ? "\n" : "");
}

int main() {
  const auto original = {9, 6, 5, 2, 3, 1, 7, 8};

  std::vector<int> vi{};
  auto even = [](int x) { return 0 == (x % 2); };

  print("Original vector:\t", original.begin(), original.end(), "\n");

  vi = original;
  const auto ret1 = rng::stable_partition(vi, even);
  print("Stable partitioned:\t", vi.begin(), ret1.begin(), 0);
  print("│ ", ret1.begin(), ret1.end());

  vi = original;
  const auto ret2 = rng::partition(vi, even);
  print("Partitioned:\t\t", vi.begin(), ret2.begin(), 0);
  print("│ ", ret2.begin(), ret2.end());

  vi = {16, 30, 44, 30, 15, 24, 10, 18, 12, 35};
  print("Unsorted vector: ", vi.begin(), vi.end());

  stable_sort(rng::begin(vi), rng::end(vi));
  print("Sorted vector:   ", vi.begin(), vi.end());
  std::array v{1, 2, 3, 4, 5, 6, 7, 8, 9};

  auto is_even = [](int i) { return i % 2 == 0; };
  auto print_seq = [](auto rem, auto first, auto last) {
    for (std::cout << rem; first != last; std::cout << *first++ << ' ') {
    }
    std::cout << '\n';
  };
  std::ranges::partition(v, is_even);
  print_seq("After partitioning, v: ", v.cbegin(), v.cend());

  const auto pp = std::ranges::partition_point(v, is_even);
  const auto i = std::ranges::distance(v.cbegin(), pp);
  std::cout << "Partition point is at " << i << "; v[" << i << "] = " << *pp
            << '\n';

  print_seq("First partition (all even elements): ", v.cbegin(), pp);
  print_seq("Second partition (all odd elements): ", pp, v.cend());
}
// namespace ranges = std::ranges;
// template <class I, std::sentinel_for<I> S, class Cmp = std::ranges::less>
//   requires std::sortable<I, Cmp>
// void quicksort(I first, S last, Cmp cmp = Cmp{}) {
//   using reference = std::iter_reference_t<I>;

//   if (first == last)
//     return;

//   auto size = ranges::distance(first, last);
//   auto pivot = ranges::next(first, size - 1);
//   ranges::iter_swap(pivot, ranges::next(first, size / 2));

//   auto tail = ranges::partition(first, pivot, [=](reference em) {
//     return std::invoke(cmp, em, *pivot); // em < pivot
//   });

//   ranges::iter_swap(pivot, tail.begin());
//   quicksort(first, tail.begin(), std::ref(cmp));
//   quicksort(ranges::next(tail.begin()), last, std::ref(cmp));
// }

// int main(int argc, char *argv[]) {

//   std::ostream_iterator<int> cout{std::cout, " "};

//   std::vector<int> v{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
//   std::cout << "Original vector:  \t";
//   ranges::copy(v, cout);

//   auto tail = ranges::partition(v, [](int i) { return i % 2 == 0; });

//   std::cout << "\nPartitioned vector: \t";
//   ranges::copy(ranges::begin(v), ranges::begin(tail), cout);
//   std::cout << "│ ";
//   ranges::copy(tail, cout);

//   std::forward_list<int> fl{1, 30, -4, 3, 5, -4, 1, 6, -8, 2, -5, 64, 1, 92};
//   std::cout << "\nUnsorted list: \t\t";
//   ranges::copy(fl, cout);

//   quicksort(ranges::begin(fl), ranges::end(fl), ranges::greater{});
//   std::cout << "\nQuick-sorted list: \t";
//   ranges::copy(fl, cout);

//   std::cout << '\n';
//   // std::array<int, 9> v{1, 2, 3, 4, 5, 6, 7, 8, 9};
//   // auto is_even = [](int i) { return i % 2 == 0; };
//   // std::cout << "原来的 vector：\n    ";
//   // std::ranges::copy(v, cout);

//   // auto it = std::ranges::partition(v, [](int i) { return i % 2 == 0; });

//   // std::cout << "\n划分后的 vector：\n    ";
//   // // std::ranges::copy(v, std::ostream_iterator<int>(std::cout, " "));

//   // // std::copy(std::begin(v), it, std::ostream_iterator<int>(std::cout, "
//   // ")); std::ranges::copy(std::ranges::begin(v), std::ranges::begin(it),
//   // cout); std::cout << "| "; std::ranges::copy(it, cout); std::copy(it,
//   // std::end(v), std::ostream_iterator<int>(std::cout, " "));

//   // std::cout.setf(std::ios_base::boolalpha);
//   // std::cout << std::is_partitioned(v.begin(), v.end(), is_even) << " ";
//   // std::partition(v.begin(), v.end(), is_even);
//   // std::cout << std::is_partitioned(v.begin(), v.end(), is_even) << " ";
//   return 0;
// }
