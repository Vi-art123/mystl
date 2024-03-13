//
// Created by wyx on 2024/2/28.
// 二叉树
//
#pragma once

#include <iostream>
#include <memory>
#include <queue>

namespace mystd
{
    template<class T>
    struct TreeNode
    {
        T value;
        std::weak_ptr<TreeNode> parent;
        std::shared_ptr<TreeNode> left;
        std::shared_ptr<TreeNode> right;
        TreeNode(const T& val, std::weak_ptr<TreeNode> p) : value(val), parent(p) {}
        ~TreeNode() { std::cout << "delete TreeNode: " << value << std::endl; }
    };


    template<class T>
    class BinaryTree
    {
    public:
        BinaryTree() = default;
        ~BinaryTree() { clear(); }

        void add(const T& value);
        void clear();
        void preOrderTraverse();
        void inOrderTraverse();
        void postOrderTraverse();
        void levelOrderTraverse();
        [[nodiscard]] size_t size() const { return m_size; }
        [[nodiscard]] bool isEmpty() const { return m_size == 0; }
    private:
        int compare(const T& v1, const T& v2);
        std::shared_ptr<TreeNode<T>> predecessor(std::shared_ptr<TreeNode<T>> node);
        std::shared_ptr<TreeNode<T>> successor(std::shared_ptr<TreeNode<T>> node);
        void preOrderTraverse(std::shared_ptr<TreeNode<T>> node);
        void inOrderTraverse(std::shared_ptr<TreeNode<T>> node);
        void postOrderTraverse(std::shared_ptr<TreeNode<T>> node);
    private:
        size_t m_size = 0;
        std::shared_ptr<TreeNode<T>> root;
    };

    template<class T>
    inline void BinaryTree<T>::clear()
    {
        root = nullptr; // 自动释放内存
        m_size = 0;
    }

    template<class T>
    void BinaryTree<T>::add(const T& value)
    {
        // 第一次添加
        if (root == nullptr) {
            root = std::make_shared<TreeNode<T>>(value, root);
            m_size++;
            return;
        }

        int cmp = 0;
        auto node = root;
        auto parent = root;
        while (node != nullptr) {
            parent = node;
            cmp = compare(node->value, value);
            if (cmp > 0) {
                node = node->left;
            } else if (cmp < 0) {
                node = node->right;
            } else {    // 相等则覆盖
                node->value = value;
                return;
            }
        }

        auto new_node = std::make_shared<TreeNode<T>>(value, parent);
        if (cmp > 0) {
            parent->left = new_node;
        } else {
            parent->right = new_node;
        }
        m_size++;
    }

    template<class T>
    inline int BinaryTree<T>::compare(const T &v1, const T &v2)
    {
        return v1 - v2;
    }

    /**
     * 前序遍历
     */
    template<class T>
    inline void BinaryTree<T>::preOrderTraverse()
    {
        if (root == nullptr) return;
        preOrderTraverse(root);
    }

    template<class T>
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
    template<class T>
    inline void BinaryTree<T>::inOrderTraverse()
    {
        if (root == nullptr) return;
        inOrderTraverse(root);
    }

    template<class T>
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
    template<class T>
    inline void BinaryTree<T>::postOrderTraverse()
    {
        if (root == nullptr) return;
        postOrderTraverse(root);
    }

    template<class T>
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
    template<class T>
    void BinaryTree<T>::levelOrderTraverse()
    {
        if (root == nullptr) return;
        std::queue<std::shared_ptr<TreeNode<T>>> qp;
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
     * 寻找某个节点的前驱节点
     * @param node
     * @return
     */
    template<class T>
    std::shared_ptr<TreeNode<T>> BinaryTree<T>::predecessor(std::shared_ptr<TreeNode<T>> node)
    {
        if (node == nullptr) return node;

        std::weak_ptr<TreeNode<T>> wp = node->left;
        if (wp.lock() != nullptr) {
            while (wp.lock()->right != nullptr)
            {
                wp = wp.lock()->right;
            }

            return wp.lock();
        }

        wp = node;
        while (wp.lock()->parent.lock() != nullptr && wp.lock() == wp.lock()->parent.lock()->right)
        {
            wp = wp.lock()->parent;
        }

        return wp.lock()->parent.lock();
    }

    /**
     * 寻找某个节点的后继节点
     * @param node
     * @return
     */
    template<class T>
    std::shared_ptr<TreeNode<T>> BinaryTree<T>::successor(std::shared_ptr<TreeNode<T>> node)
    {
        if (node == nullptr) return node;

        std::weak_ptr<TreeNode<T>> wp = node->right;
        if (wp.lock() != nullptr) {
            while (wp.lock()->left != nullptr)
            {
                wp = wp.lock()->left;
            }

            return wp.lock();
        }

        wp = node;
        while (wp.lock()->parent.lock() != nullptr && wp.lock() == wp.lock()->parent.lock()->left)
        {
            wp = wp.lock()->parent;
        }

        return wp.lock()->parent.lock();
    }
} // mystd
