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


    template<typename T>
    class BinaryTree
    {
    public:
        void add(const T& value);
        void remove(const T& value) { remove(get_node(value)); }
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
        std::shared_ptr<TreeNode<T>> get_node(const T& value);
        void remove(std::shared_ptr<TreeNode<T>> node);
        void preOrderTraverse(std::shared_ptr<TreeNode<T>> node);
        void inOrderTraverse(std::shared_ptr<TreeNode<T>> node);
        void postOrderTraverse(std::shared_ptr<TreeNode<T>> node);
    private:
        size_t m_size = 0;
        std::shared_ptr<TreeNode<T>> root;
    };

    template<typename T>
    inline void BinaryTree<T>::clear()
    {
        root = nullptr; // 自动释放内存
        m_size = 0;
    }

    template<typename T>
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

    template<typename T>
    void BinaryTree<T>::remove(std::shared_ptr<TreeNode<T>> node)
    {
        if (node == nullptr) return;
        m_size--;

        if (node->hasTwoChildren()) {   // 度为2的节点
            // 找到前驱节点或后继节点的值
            auto p = predecessor(node);
            // 将前驱节点或后继节点的值覆盖当前节点
            node->value = p->value;
            // 将前驱节点或后继节点删除
            node = p;
        }

        // 删除node节点，到达此处node的度必然是1或者0
        decltype(node) replacement = node->left != nullptr ? node->left : node->right;
        if (replacement != nullptr) {   // node是度为1的节点
            // 更改parent
            replacement->parent = node->parent;

            // 更改parent的left或right指向
            if (!node->parent.lock()) { // node是度为1的节点，并且是根节点
                root = replacement;
            } else if (node == node->parent.lock()->left) {
                node->parent.lock()->left = replacement;
            } else {    // node == node->parent.lock()->right
                node->parent.lock()->right = replacement;
            }
        } else if (!node->parent.lock()) {    // node是叶子节点并且是根节点
            root = nullptr;
        } else {    // node是叶子节点，但不是根节点
            if (node == node->parent.lock()->left) {
                node->parent.lock()->left = nullptr;
            } else {    // node == node->parent.lock()->righ
                node->parent.lock()->right = nullptr;
            }
        }
    }

    template<typename T>
    inline int BinaryTree<T>::compare(const T& v1, const T& v2)
    {
        return v1 - v2;
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

    template<typename T>
    std::shared_ptr<TreeNode<T>> BinaryTree<T>::get_node(const T &value)
    {
        auto node = root;
        while (node != nullptr)
        {
            int cmp = compare(node->value, value);
            if (cmp == 0) return node;
            if (cmp > 0) {
                node = node->left;
            } else {
                node = node->right;
            }
        }

        return nullptr;
    }
} // mystd
