/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cc                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TYTY000 <767280080@qq.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 16:17:28 by TYTY000           #+#    #+#             */
/*   Updated: 2024/05/05 16:29:04 by TYTY000          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <array>
template <const char *str> struct Message {};
static const char hello17[] = "Hello World!"; // 无 链 接
Message<hello17> msg17;                       // 自 从C++17起OK
// Message<"hi"> msgError;                       // ERRO

// int num;
// constexpr int *pNum() { return &num; }
// template <int *p> struct A {};
// A<pNum()> b; // C++17之 前ERROR， 现 在OK

template <auto N> struct S {};
S<42> s;
S<'a'> sa;

template <typename T, auto N> struct A {
  A(const std::array<T, N> &) {}
  A(T (&)[N]) {}
};
A sb{"ab"};
std::array<double, 10> sa1;
A a1{sa1};
