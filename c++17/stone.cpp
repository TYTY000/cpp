/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stone.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TYTY000 <767280080@qq.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 14:01:28 by TYTY000           #+#    #+#             */
/*   Updated: 2024/08/09 14:52:39 by TYTY000          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>
#include <iostream>
#include <numeric>
#include <ostream>
#include <vector>
using namespace std;

vector<int> stones = {31, 26, 33, 21, 40};

int main(int argc, char *argv[]) {
    int sum = accumulate(stones.begin(), stones.end(), 0);
    vector<int> dp(sum / 2 + 1, 0);
    for (int i = 0; i < stones.size(); i++) {
        cout << "i = " << i << endl;
        for (int j = sum / 2; j >= stones[i]; j--) {
            dp[j] = max(dp[j], dp[j - stones[i]] + stones[i]);
            cout << "j = " << j << endl;
            std::cout << "v = { ";
            for (int n : dp) std::cout << n << ", ";
            std::cout << "}; \n";
        }
    }
    cout << sum - 2 * dp[sum / 2];
    return 0;
}
