/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodetrav.cc                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TYTY000 <767280080@qq.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 16:03:50 by TYTY000           #+#    #+#             */
/*   Updated: 2024/08/10 13:29:42 by TYTY000          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

struct Node {
    int value;
    Node *subLeft{nullptr};
    Node *subRight{nullptr};
    Node(int i = 0) : value{i} {}
    int getValue() const { return value; }
    // 遍 历 辅 助 函 数：
    static constexpr auto left = &Node::subLeft;
    static constexpr auto right = &Node::subRight;
    // 使 用 折 叠 表 达 式 遍 历 树：
    template <typename T, typename... TP>
    static Node *traverse(T np, TP... paths) {
        return (np->*...->*paths);  // np ‐>* paths1 ‐>* paths2
    }
};
#include <iostream>
int main() {
    // 初 始 化 二 叉 树 结 构：
    Node *root = new Node{0};
    root->subLeft = new Node{1};
    root->subLeft->subRight = new Node{2};
    // 遍 历 二 叉 树：
    Node *node = Node::traverse(root, Node::left, Node::right);
    std::cout << node->getValue() << '\n';
    node = root->*Node::left->*Node::right;
    std::cout << node->getValue() << '\n';
    node = root->subLeft->subRight;
    std::cout << node->getValue() << '\n';
}
