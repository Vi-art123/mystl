//
// Created by wyx on 2024/3/21.
// 二叉搜索树
//
#pragma once

#include "BinaryTree.hpp"

namespace mystd
{
    template<typename T>
    class BST : public BinaryTree<T>
    {
    public:
        void add(const T& value);
        void remove(const T& value) { remove(get_node(value)); }
        [[nodiscard]] bool contains(const T& value) { return get_node(value) != nullptr; }
    private:
        int compare(const T& v1, const T& v2);
        std::shared_ptr<TreeNode<T>> get_node(const T& value);
        void remove(std::shared_ptr<TreeNode<T>> node);
        virtual void afterAdd(std::shared_ptr<TreeNode<T>> node) {}
        virtual void afterRemove(std::shared_ptr<TreeNode<T>> node) {}
    };

    template<typename T>
    void BST<T>::add(const T& value)
    {
        // 第一次添加
        if (this->root == nullptr) {
            this->root = this->createNode(value, this->root);
            this->m_size++;
            // 新添加节点之后的处理
            afterAdd(this->root);
            return;
        }

        int cmp = 0;
        auto node = this->root;
        auto parent = this->root;
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

        auto new_node = this->createNode(value, parent);
        if (cmp > 0) {
            parent->left = new_node;
        } else {
            parent->right = new_node;
        }
        this->m_size++;

        // 新添加节点之后的处理
        afterAdd(new_node);
    }

    template<typename T>
    void BST<T>::remove(std::shared_ptr<TreeNode<T>> node)
    {
        if (node == nullptr) return;
        this->m_size--;

        if (node->hasTwoChildren()) {   // 度为2的节点
            // 找到前驱节点或后继节点的值
            auto p = this->predecessor(node);
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
                this->root = replacement;
            } else if (node == node->parent.lock()->left) {
                node->parent.lock()->left = replacement;
            } else {    // node == node->parent.lock()->right
                node->parent.lock()->right = replacement;
            }

            // 删除节点之后的处理
            afterRemove(node);
        } else if (!node->parent.lock()) {    // node是叶子节点并且是根节点
            this->root = nullptr;

            // 删除节点之后的处理
            afterRemove(node);
        } else {    // node是叶子节点，但不是根节点
            if (node == node->parent.lock()->left) {
                node->parent.lock()->left = nullptr;
            } else {    // node == node->parent.lock()->righ
                node->parent.lock()->right = nullptr;
            }

            // 删除节点之后的处理
            afterRemove(node);
        }
    }

    template<typename T>
    inline int BST<T>::compare(const T& v1, const T& v2)
    {
        return v1 - v2;
    }

    template<typename T>
    std::shared_ptr<TreeNode<T>> BST<T>::get_node(const T &value)
    {
        auto node = this->root;
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
}