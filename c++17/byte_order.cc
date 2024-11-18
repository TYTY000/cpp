/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   byte_order.cc                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TYTY000 <767280080@qq.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 15:33:18 by TYTY000           #+#    #+#             */
/*   Updated: 2024/08/15 15:33:18 by TYTY000          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <arpa/inet.h>

#include <cstdint>
#include <iostream>

int main() {
    uint32_t num = 0x12345678;
    uint32_t n_num = htonl(num);    // Host to Network Long
    uint32_t h_num = ntohl(n_num);  // Network to Host Long

    std::cout << "Original: " << std::hex << num << std::endl;
    std::cout << "Network Byte Order: " << std::hex << n_num << std::endl;
    std::cout << "Converted Back: " << std::hex << h_num << std::endl;

    return 0;
}
