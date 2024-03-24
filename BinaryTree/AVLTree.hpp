//
// Created by wyx on 2024/3/21.
// AVL树
//
#pragma once

#include "BBSTree.hpp"

namespace mystd
{
    template<typename T>
    struct AVLNode : public TreeNode<T>
    {
        int height = 1; // 初始高度为1

        AVLNode(const T& val, std::weak_ptr<TreeNode<T>> p) : TreeNode<T>(val, p) {}
        
        /**
         * 获取节点的平衡因子
         * @return 
         */        
        [[nodiscard]] int balanceFactor() const
        {
            auto avl_left = std::dynamic_pointer_cast<AVLNode<T>>(this->left);
            auto avl_right = std::dynamic_pointer_cast<AVLNode<T>>(this->right);
            int left_height = avl_left == nullptr ? 0 : avl_left->height;
            int right_height = avl_right == nullptr ? 0 : avl_right->height;
            return left_height - right_height;
        }

        /**
         * 更新节点的高度
         */        
        void updateHeight()
        {
            auto avl_left = std::dynamic_pointer_cast<AVLNode<T>>(this->left);
            auto avl_right = std::dynamic_pointer_cast<AVLNode<T>>(this->right);
            int left_height = avl_left == nullptr ? 0 : avl_left->height;
            int right_height = avl_right == nullptr ? 0 : avl_right->height;
            height = 1 + std::max(left_height, right_height);
        }

        /**
         * 获取高度比较高的子树
         * @return 
         */        
        std::shared_ptr<TreeNode<T>> tallerChild() const
        {
            auto avl_left = std::dynamic_pointer_cast<AVLNode<T>>(this->left);
            auto avl_right = std::dynamic_pointer_cast<AVLNode<T>>(this->right);
            int left_height = avl_left == nullptr ? 0 : avl_left->height;
            int right_height = avl_right == nullptr ? 0 : avl_right->height;
            if (left_height > right_height) return this->left;
            if (left_height < right_height) return this->right;
            return this->isLeftChild() ? this->left : this->right;  // 如果左右子树高度相等，则返回与自己同方向的子树
        }

        [[nodiscard]] std::string toString() const override
        {
            std::string str = std::to_string(this->value);
            str.append("_p(");
            if (auto p = this->parent.lock()) {
                str.append(std::to_string(p->value));
            } else {
                str.append("null");
            }
            str.push_back(')');

            str.append("_h(");
            str.append(std::to_string(height));
            str.push_back(')');

            return str;
        }
    };

    template<typename T>
    class AVLTree : public BBSTree<T>
    {
    protected:
        std::shared_ptr<TreeNode<T>> createNode(const T& value, std::shared_ptr<TreeNode<T>> parent) override
        {
            return std::make_shared<AVLNode<T>>(value, parent);
        }

        void afterRotate(std::shared_ptr<TreeNode<T>> grand,
                                 std::shared_ptr<TreeNode<T>> parent,
                                 std::shared_ptr<TreeNode<T>> child) override;
        void rotate(std::shared_ptr<TreeNode<T>> r,
                    std::shared_ptr<TreeNode<T>> b, std::shared_ptr<TreeNode<T>> c,
                    std::shared_ptr<TreeNode<T>> d,
                    std::shared_ptr<TreeNode<T>> e, std::shared_ptr<TreeNode<T>> f) override;
    private:
        void afterAdd(std::shared_ptr<TreeNode<T>> node) override;
        void afterRemove(std::shared_ptr<TreeNode<T>> node) override;
        void updateHeight(std::shared_ptr<TreeNode<T>> node);
        void rebalance(std::shared_ptr<TreeNode<T>> grand);
        [[maybe_unused]] void rebalance2(std::shared_ptr<TreeNode<T>> grand);
        bool isBalanced(std::shared_ptr<TreeNode<T>> node) const;
    };

    /**
     * 新添加节点之后的处理
     * @param node 新添加的节点
     */
    template<typename T>
    void AVLTree<T>::afterAdd(std::shared_ptr<TreeNode<T>> node)
    {
        while ((node = node->parent.lock()) != nullptr)
        {
            if (isBalanced(node)) {
                // 更新高度
                updateHeight(node);
            } else {
                // 恢复平衡
                rebalance(node);
                // 找到第一个不平衡的节点，恢复平衡后整棵树就平衡了
                break;
            }
        }
    }

    /**
     * 删除节点之后的处理
     * @param node
     */
    template<typename T>
    void AVLTree<T>::afterRemove(std::shared_ptr<TreeNode<T>> node)
    {
        while ((node = node->parent.lock()) != nullptr)
        {
            if (isBalanced(node)) {
                // 更新高度
                updateHeight(node);
            } else {
                // 恢复平衡
                rebalance(node);
            }
        }
    }

    template<typename T>
    inline void AVLTree<T>::updateHeight(std::shared_ptr<TreeNode<T>> node)
    {
        std::dynamic_pointer_cast<AVLNode<T>>(node)->updateHeight();
    }

    /**
     * 恢复平衡（使用统一的旋转操作）
     * @param grand 高度最低的那个不平衡点
     */
    template<typename T>
    void AVLTree<T>::rebalance(std::shared_ptr<TreeNode<T>> grand)
    {
        auto parent = std::dynamic_pointer_cast<AVLNode<T>>(grand)->tallerChild();
        auto node = std::dynamic_pointer_cast<AVLNode<T>>(parent)->tallerChild();
        if (parent->isLeftChild()) {
            if (node->isLeftChild()) { // LL
                rotate(grand, node, node->right, parent, parent->right, grand);
            } else {    // LR
                rotate(grand, parent, node->left, node, node->right, grand);
            }
        } else {
            if (node->isLeftChild()) { // RL
                rotate(grand, grand, node->left, node, node->right, parent);
            } else {    // RR
                rotate(grand, grand, parent->left, parent, node->left, node);
            }
        }
    }

    /**
     * 恢复平衡（根据方向判断进行对应的旋转操作）
     * @param grand 高度最低的那个不平衡点
     */
    template<typename T>
    [[maybe_unused]] void AVLTree<T>::rebalance2(std::shared_ptr<TreeNode<T>> grand)
    {
        auto parent = std::dynamic_pointer_cast<AVLNode<T>>(grand)->tallerChild();
        auto node = std::dynamic_pointer_cast<AVLNode<T>>(parent)->tallerChild();
        if (parent->isLeftChild()) {
            if (node->isLeftChild()) { // LL
                this->rotateRight(grand);
            } else {    // LR
                this->rotateLeft(parent);
                this->rotateRight(grand);
            }
        } else {
            if (node->isLeftChild()) { // RL
                this->rotateRight(parent);
                this->rotateLeft(grand);
            } else {    // RR
                this->rotateLeft(grand);
            }
        }
    }

    template<typename T>
    void AVLTree<T>::afterRotate(std::shared_ptr<TreeNode<T>> grand,
                                 std::shared_ptr<TreeNode<T>> parent,
                                 std::shared_ptr<TreeNode<T>> child)
    {
        BBSTree<T>::afterRotate(grand, parent, child);
        // 更新高度(先更新矮的，再更新高的)
        updateHeight(grand);
        updateHeight(parent);
    }

    /**
     * 统一旋转操作
     */
    template<typename T>
    void AVLTree<T>::rotate(std::shared_ptr<TreeNode<T>> r, // 子树的根节点
                            std::shared_ptr<TreeNode<T>> b, std::shared_ptr<TreeNode<T>> c,
                            std::shared_ptr<TreeNode<T>> d,
                            std::shared_ptr<TreeNode<T>> e, std::shared_ptr<TreeNode<T>> f)
    {
        BBSTree<T>::rotate(r, b, c, d, e, f);
        // 更新高度(先更新矮的，再更新高的)
        updateHeight(b);
        updateHeight(f);
        updateHeight(d);
    }

    template<typename T>
    inline bool AVLTree<T>::isBalanced(std::shared_ptr<TreeNode<T>> node) const
    {
        return std::abs(std::dynamic_pointer_cast<AVLNode<T>>(node)->balanceFactor()) <= 1;
    }
}