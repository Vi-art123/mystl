//
// Created by wyx on 2024/3/23.
// 平衡二叉搜索树基类
//
#pragma once

#include "BSTree.hpp"

namespace mystd
{
    template<typename T>
    class BBSTree : public BSTree<T>
    {
    protected:
        void rotateLeft(std::shared_ptr<TreeNode<T>> grand);
        void rotateRight(std::shared_ptr<TreeNode<T>> grand);
        virtual void afterRotate(std::shared_ptr<TreeNode<T>> grand,
                         std::shared_ptr<TreeNode<T>> parent,
                         std::shared_ptr<TreeNode<T>> child);
        virtual void rotate(std::shared_ptr<TreeNode<T>> r,
                    std::shared_ptr<TreeNode<T>> b, std::shared_ptr<TreeNode<T>> c,
                    std::shared_ptr<TreeNode<T>> d,
                    std::shared_ptr<TreeNode<T>> e, std::shared_ptr<TreeNode<T>> f);
    };

    template<typename T>
    void BBSTree<T>::rotateLeft(std::shared_ptr<TreeNode<T>> grand)
    {
        auto parent = grand->right;
        auto child = parent->left;
        grand->right = child;
        parent->left = grand;

        // 执行旋转后的操作
        afterRotate(grand, parent, child);
    }

    template<typename T>
    void BBSTree<T>::rotateRight(std::shared_ptr<TreeNode<T>> grand)
    {
        auto parent = grand->left;
        auto child = parent->right;
        grand->left = child;
        parent->right = grand;

        // 执行旋转后的操作
        afterRotate(grand, parent, child);
    }

    template<typename T>
    void BBSTree<T>::afterRotate(std::shared_ptr<TreeNode<T>> grand,
                                 std::shared_ptr<TreeNode<T>> parent,
                                 std::shared_ptr<TreeNode<T>> child)
    {
        // 让parent成为子树的根节点
        parent->parent = grand->parent;
        if (grand->isLeftChild()) {
            grand->parent.lock()->left = parent;
        } else if (grand->isRightChild()) {
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
    }

    /**
     * 统一旋转操作
     */
    template<typename T>
    void BBSTree<T>::rotate(std::shared_ptr<TreeNode<T>> r, // 子树的根节点
                            std::shared_ptr<TreeNode<T>> b, std::shared_ptr<TreeNode<T>> c,
                            std::shared_ptr<TreeNode<T>> d,
                            std::shared_ptr<TreeNode<T>> e, std::shared_ptr<TreeNode<T>> f)
    {
        // 让d成为子树的根节点
        d->parent = r->parent;
        if (r->isLeftChild()) {
            r->parent.lock()->left = d;
        } else if (r->isRightChild()) {
            r->parent.lock()->right = d;
        } else {
            this->root = d;
        }

        // b-c的处理
        b->right = c;
        if (c != nullptr) {
            c->parent = b;
        }

        // e-f的处理
        f->left = e;
        if (e != nullptr) {
            e->parent = f;
        }

        // b-f的处理
        d->left = b;
        d->right = f;
        b->parent = d;
        f->parent = d;
    }
}