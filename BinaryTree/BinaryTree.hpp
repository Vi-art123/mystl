//
// Created by wyx on 2024/2/28.
// 二叉树基类
//
#pragma once

#include <iostream>
#include <queue>
#include "TreeNode.h"

namespace mystd
{
    template<typename T>
    class BinaryTree
    {
    public:
        BinaryTree() = default;
        BinaryTree(const BinaryTree& bt) = default;
        BinaryTree(BinaryTree&& bt) = default;
        virtual ~BinaryTree() = default;
         
        void clear() noexcept;
        void preOrderTraverse();
        void inOrderTraverse();
        void postOrderTraverse();
        void levelOrderTraverse();
        [[nodiscard]] int height() const;
        [[nodiscard]] int height2() const { return height2(root); };
        [[nodiscard]] int size() const noexcept { return m_size; }
        [[nodiscard]] bool isEmpty() const noexcept { return m_size == 0; }
    protected:
        std::shared_ptr<TreeNode<T>> predecessor(std::shared_ptr<TreeNode<T>> node);
        std::shared_ptr<TreeNode<T>> successor(std::shared_ptr<TreeNode<T>> node);
    private:
        int height2(std::shared_ptr<TreeNode<T>> node) const;
        virtual void preOrderTraverse(std::shared_ptr<TreeNode<T>> node);
        virtual void inOrderTraverse(std::shared_ptr<TreeNode<T>> node);
        virtual void postOrderTraverse(std::shared_ptr<TreeNode<T>> node);
    protected:
        int m_size = 0;
        std::shared_ptr<TreeNode<T>> root;
    };

    template<typename T>
    inline void BinaryTree<T>::clear() noexcept
    {
        root = nullptr; // 自动释放内存
        m_size = 0;
    }

    /**
     * 前序遍历
     */
    template<typename T>
    inline void BinaryTree<T>::preOrderTraverse()
    {
        if (root == nullptr) return;
        preOrderTraverse(root);
    }

    template<typename T>
    void BinaryTree<T>::preOrderTraverse(std::shared_ptr<TreeNode<T>> node)
    {
        if (node == nullptr) return;
        std::cout << node->value << " ";
        preOrderTraverse(node->left);
        preOrderTraverse(node->right);
    }

    /**
     * 中序遍历
     */
    template<typename T>
    inline void BinaryTree<T>::inOrderTraverse()
    {
        if (root == nullptr) return;
        inOrderTraverse(root);
    }

    template<typename T>
    void BinaryTree<T>::inOrderTraverse(std::shared_ptr<TreeNode<T>> node)
    {
        if (node == nullptr) return;
        inOrderTraverse(node->left);
        std::cout << node->value << " ";
        inOrderTraverse(node->right);
    }

    /**
     * 后序遍历
     */
    template<typename T>
    inline void BinaryTree<T>::postOrderTraverse()
    {
        if (root == nullptr) return;
        postOrderTraverse(root);
    }

    template<typename T>
    void BinaryTree<T>::postOrderTraverse(std::shared_ptr<TreeNode<T>> node)
    {
        if (node == nullptr) return;
        postOrderTraverse(node->left);
        postOrderTraverse(node->right);
        std::cout << node->value << " ";
    }

    /**
     * 层序遍历
     */
    template<typename T>
    void BinaryTree<T>::levelOrderTraverse()
    {
        if (root == nullptr) return;
        std::queue<decltype(root)> qp;
        qp.push(root);
        while (!qp.empty())
        {
            auto node = qp.front();
            qp.pop();
            std::cout << node->value << " ";
            if (node->left != nullptr) {
                qp.push(node->left);
            }

            if (node->right != nullptr) {
                qp.push(node->right);
            }
        }
    }

    /**
     * 层序遍历方式
     * @return 
     */    
    template<typename T>
    int BinaryTree<T>::height() const
    {
        if (root == nullptr) return 0;
        int height__ = 0;   // 树的高度
        int levelRowSize = 1;  // 每一层的元素个数
        std::queue<decltype(root)> qp;
        qp.push(root);
        while (!qp.empty())
        {
            auto node = qp.front();
            qp.pop();
            levelRowSize--;

            if (node->left != nullptr) {
                qp.push(node->left);
            }

            if (node->right != nullptr) {
                qp.push(node->right);
            }

            if (levelRowSize == 0) {    // 意味着即将进入下一层
                levelRowSize = qp.size();
                height__++;
            }
        }
        return height__;
    }

    /**
     * 递归方式
     * @param node
     * @return 
     */    
    template<typename T>
    int BinaryTree<T>::height2(std::shared_ptr<TreeNode<T>> node) const
    {
        if (node == nullptr) return 0;
        return 1 + std::max(height2(node->left), height2(node->right));
    }

    /**
     * 寻找某个节点的前驱节点
     * @param node
     * @return
     */
    template<typename T>
    std::shared_ptr<TreeNode<T>> BinaryTree<T>::predecessor(std::shared_ptr<TreeNode<T>> node)
    {
        if (node == nullptr) return node;

        // 前驱节点在左子树当中(left.right.right....)
        auto p = node->left;
        if (p != nullptr) {
            while (p->right != nullptr)
            {
                p = p->right;
            }
            return p;
        }

        // 从父节点、祖父节点中寻找前驱节点
        while (node->parent.lock() && node == node->parent.lock()->left)
        {
            node = node->parent.lock();
        }

        return node->parent.lock();
    }

    /**
     * 寻找某个节点的后继节点
     * @param node
     * @return
     */
    template<typename T>
    std::shared_ptr<TreeNode<T>> BinaryTree<T>::successor(std::shared_ptr<TreeNode<T>> node)
    {
        if (node == nullptr) return node;

        // 后继节点在左子树当中(right.left.left....)
        auto p = node->right;
        if (p != nullptr) {
            while (p->left != nullptr)
            {
                p = p->left;
            }

            return p;
        }

        // 从父节点、祖父节点中寻找后继节点
        while (node->parent.lock() && node == node->parent.lock()->right)
        {
            node = node->parent.lock();
        }

        return node->parent.lock();
    }
} // mystd