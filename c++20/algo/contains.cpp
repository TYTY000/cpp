/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contains.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jiang <767280080@qq.com>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 10:42:49 by Jiang             #+#    #+#             */
/*   Updated: 2024/08/09 16:26:06 by TYTY000          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>
#include <array>
#include <ranges>

// C++ 23
int main() {
    constexpr auto haystack = std::array{3, 1, 4, 1, 5};
    constexpr auto needle = std::array{1, 4, 1};
    constexpr auto bodkin = std::array{2, 5, 2};
    auto increment = [](int x) { return ++x; };
    auto decrement = [](int x) { return --x; };

    static_assert(
        std::ranges::contains(haystack, 4) &&
        !std::ranges::contains(haystack, 6) &&
        std::ranges::contains_subrange(haystack, needle) &&
        !std::ranges::contains_subrange(haystack, bodkin) &&
        std::ranges::contains(haystack, 6, increment) &&
        !std::ranges::contains(haystack, 1, increment) &&
        std::ranges::contains_subrange(haystack, bodkin, {}, increment) &&
        !std::ranges::contains_subrange(haystack, bodkin, {}, decrement) &&
        std::ranges::contains_subrange(haystack, bodkin, {}, {}, decrement));
}
