/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cc                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TYTY000 <767280080@qq.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 15:58:56 by TYTY000           #+#    #+#             */
/*   Updated: 2024/08/10 13:41:47 by TYTY000          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
// 可 变 数 量 基 类 的 模 板
template <typename... Bases>
class MultiBase : private Bases... {
   public:
    void print() {
        // 调 用 所 有 基 类 的print()函 数
        (..., Bases::print());
    }

    template <std::size_t... Is>
    void print2_impl(std::index_sequence<Is...>) {
        // 调用所有基类的print()函数，逆序展开
        (void(std::initializer_list<int>{
            (std::get<sizeof...(Bases) - 1 - Is>(
                 std::tie(static_cast<Bases&>(*this)...))
                 .print(),
             0)...}));
    }

    void print2() { print2_impl(std::make_index_sequence<sizeof...(Bases)>{}); }
};
struct A {
    void print() { std::cout << "A::print()"; }
};
struct B {
    void print() { std::cout << "B::print()"; }
};
struct C {
    void print() { std::cout << "C::print()"; }
};
int main() {
    MultiBase<A, B, C> mb;
    mb.print();
    mb.print2();
}
