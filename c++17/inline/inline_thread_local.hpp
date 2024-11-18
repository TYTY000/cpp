/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inline_thread_local.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TYTY000 <767280080@qq.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 09:22:12 by TYTY000           #+#    #+#             */
/*   Updated: 2024/05/05 09:22:35 by TYTY000          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>

struct MyData {
  inline static std::string gName = "global";
  inline static thread_local std::string tName = "thread";
  std::string iName = "local";
  void print(const std::string &msg) const {
    std::cout << msg << '\n';
    std::cout << "‐ gName: " << gName << '\n';
    std::cout << "‐ tName: " << tName << '\n';
    std::cout << "‐ lName: " << iName << '\n';
  }
};

inline thread_local MyData myThreadData;
