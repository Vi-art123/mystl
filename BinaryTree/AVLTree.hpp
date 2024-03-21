//
// Created by wyx on 2024/3/21.
// AVL树
//
#pragma once

#include "BST.hpp"

namespace mystd
{
    template<typename T>
    struct AVLNode : public TreeNode<T>
    {
        int height = 1;
        AVLNode(const T& val, std::weak_ptr<TreeNode<T>> p) : TreeNode<T>(val, p) {}
        [[nodiscard]] int balanceFactor() const
        {
            auto avl_left = std::dynamic_pointer_cast<AVLNode<T>>(this->left);
            auto avl_right = std::dynamic_pointer_cast<AVLNode<T>>(this->right);
            int left_height = avl_left == nullptr ? 0 : avl_left->height;
            int right_height = avl_right == nullptr ? 0 : avl_right->height;
            return left_height - right_height;
        }

        void updateHeight()
        {
            auto avl_left = std::dynamic_pointer_cast<AVLNode<T>>(this->left);
            auto avl_right = std::dynamic_pointer_cast<AVLNode<T>>(this->right);
            int left_height = avl_left == nullptr ? 0 : avl_left->height;
            int right_height = avl_right == nullptr ? 0 : avl_right->height;
            height = 1 + std::max(left_height, right_height);
        }

        std::shared_ptr<TreeNode<T>> tallerChild() const
        {
            auto avl_left = std::dynamic_pointer_cast<AVLNode<T>>(this->left);
            auto avl_right = std::dynamic_pointer_cast<AVLNode<T>>(this->right);
            int left_height = avl_left == nullptr ? 0 : avl_left->height;
            int right_height = avl_right == nullptr ? 0 : avl_right->height;
            if (left_height > right_height) return this->left;
            if (left_height < right_height) return this->right;
            return this->isLeft() ? this->left : this->right;
        }
    };

    template<typename T>
    class AVLTree : public BST<T>
    {
    protected:
        std::shared_ptr<TreeNode<T>> createNode(const T& value, std::shared_ptr<TreeNode<T>> parent) override;
    private:
        void afterAdd(std::shared_ptr<TreeNode<T>> node) override;
        void updateHeight(std::shared_ptr<TreeNode<T>> node);
        void rebalance(std::shared_ptr<TreeNode<T>> grand);
        void rotateLeft(std::shared_ptr<TreeNode<T>> grand);
        void rotateRight(std::shared_ptr<TreeNode<T>> grand);
        void afterRotate(std::shared_ptr<TreeNode<T>> grand,
                         std::shared_ptr<TreeNode<T>> parent,
                         std::shared_ptr<TreeNode<T>> child);
        bool isBalanced(std::shared_ptr<TreeNode<T>> node) const;
    };

    template<typename T>
    std::shared_ptr<TreeNode<T>> AVLTree<T>::createNode(const T &value, std::shared_ptr<TreeNode<T>> parent)
    {
        return std::make_shared<AVLNode<T>>(value, parent);
    }

    /**
     * 新添加节点之后的处理
     * @param node
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

    template<typename T>
    inline void AVLTree<T>::updateHeight(std::shared_ptr<TreeNode<T>> node)
    {
        std::dynamic_pointer_cast<AVLNode<T>>(node)->updateHeight();
    }

    /**
     * 恢复平衡
     * @param grand 高度最低的那个不平衡点
     */
    template<typename T>
    void AVLTree<T>::rebalance(std::shared_ptr<TreeNode<T>> grand)
    {
        auto parent = std::dynamic_pointer_cast<AVLNode<T>>(grand)->tallerChild();
        auto node = std::dynamic_pointer_cast<AVLNode<T>>(parent)->tallerChild();
        if (parent->isLeft()) {
            if (node->isLeft()) { // LL
                rotateRight(grand);
            } else {    // LR
                rotateLeft(parent);
                rotateRight(grand);
            }
        } else {
            if (node->isLeft()) { // RL
                rotateRight(parent);
                rotateLeft(grand);
            } else {    // RR
                rotateLeft(grand);
            }
        }
    }

    template<typename T>
    void AVLTree<T>::rotateLeft(std::shared_ptr<TreeNode<T>> grand)
    {
        auto parent = grand->right;
        auto child = parent->left;
        grand->right = child;
        parent->left = grand;

        // 执行旋转后的操作
        afterRotate(grand, parent, child);
    }

    template<typename T>
    void AVLTree<T>::rotateRight(std::shared_ptr<TreeNode<T>> grand)
    {
        auto parent = grand->left;
        auto child = parent->right;
        grand->left = child;
        parent->right = grand;

        // 执行旋转后的操作
        afterRotate(grand, parent, child);
    }

    template<typename T>
    void AVLTree<T>::afterRotate(std::shared_ptr<TreeNode<T>> grand,
                                 std::shared_ptr<TreeNode<T>> parent,
                                 std::shared_ptr<TreeNode<T>> child)
    {
        // 让parent成为子树的根节点
        parent->parent = grand->parent;
        if (grand->isLeft()) {
            grand->parent.lock()->left = parent;
        } else if (grand->isRight()) {
            grand->parent.lock()->right = parent;
        } else {    // grand是根节点
            this->root = parent;
        }

        // 更新child的parent
        if (child != nullptr) {
            child->parent = grand;
        }

        // 更新grand的parent
        grand->parent = parent;

        // 更新高度(先更新矮的，在更新高的)
        updateHeight(grand);
        updateHeight(parent);
    }

    template<typename T>
    inline bool AVLTree<T>::isBalanced(std::shared_ptr<TreeNode<T>> node) const
    {
        return std::abs(std::dynamic_pointer_cast<AVLNode<T>>(node)->balanceFactor()) <= 1;
    }
}