/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   homo.cc                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TYTY000 <767280080@qq.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 16:07:33 by TYTY000           #+#    #+#             */
/*   Updated: 2024/08/10 13:46:34 by TYTY000          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <type_traits>
template <typename T1, typename... TN>
struct IsHomo {
    static constexpr bool value = (std::is_same_v<T1, TN> && ...);
};

template <typename T1, typename... TN>
constexpr bool isHomo(T1, TN...) {
    return (std::is_same_v<T1, TN> && ...);
}

int main(int argc, char *argv[]) {
    std::cout << isHomo(1, -1, "hello", nullptr) << std::endl;
    std::cout << IsHomo<int, int, int>::value;
    return 0;
}
