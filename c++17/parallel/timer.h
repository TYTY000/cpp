/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TYTY000 <767280080@qq.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 18:07:08 by TYTY000           #+#    #+#             */
/*   Updated: 2024/05/07 18:11:01 by TYTY000          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <chrono>
#include <iostream>
#include <ratio>
#include <string>
class Timer {
private:
  std::chrono::steady_clock::time_point last;

public:
  Timer() : last(std::chrono::steady_clock::now()) {}
  void printDuration(const std::string &msg = "Duration diff : ") {
    auto now{std::chrono::steady_clock::now()};
    std::chrono::duration<double, std::milli> diff(now - last);
    std::cout << msg << diff.count() << '\n';
    last = std::chrono::steady_clock ::now();
  }
};
