//
// Created by wyx on 2024/3/21.
// 二叉树节点
//

#pragma once

#include <memory>

namespace mystd
{
    template<typename T>
    struct TreeNode
    {
        T value;
        std::weak_ptr<TreeNode> parent;
        std::shared_ptr<TreeNode> left;
        std::shared_ptr<TreeNode> right;
        TreeNode(const T& val, std::weak_ptr<TreeNode> p) : value(val), parent(p) {}
//         ~TreeNode() { std::cout << "delete TreeNode: " << value << std::endl; }

        bool hasTwoChildren()
        {
            return (left != nullptr && right != nullptr);
        }
    };
}