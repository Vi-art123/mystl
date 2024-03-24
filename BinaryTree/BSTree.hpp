//
// Created by wyx on 2024/3/21.
// 二叉搜索树
//
#pragma once

#define UNUSED(expr) (void)(expr);

#include "BinaryTree.hpp"

namespace mystd
{
    template<typename T>
    class BSTree : public BinaryTree<T>
    {
    public:
        void add(const T& value);
        void remove(const T& value) { remove(get_node(value)); }
        [[nodiscard]] bool contains(const T& value) const { return get_node(value) != nullptr; }
    private:
        int compare(const T& v1, const T& v2) const;
        std::shared_ptr<TreeNode<T>> get_node(const T& value) const;
        void remove(std::shared_ptr<TreeNode<T>> node);

        /**
         * 添加节点之后的处理（派生类重写做相应的处理）
         * @param node 新添加的节点
         */
        virtual void afterAdd(std::shared_ptr<TreeNode<T>> node) { UNUSED(node); }

        /**
         * 删除node之后的调整（派生类重写做相应的处理）
         * @param node 被删除的节点 或者 用以取代被删除节点的子节点
         */
        virtual void afterRemove(std::shared_ptr<TreeNode<T>> node) { UNUSED(node); }
    };

    template<typename T>
    void BSTree<T>::add(const T& value)
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
    void BSTree<T>::remove(std::shared_ptr<TreeNode<T>> node)
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
            afterRemove(replacement);
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
    inline int BSTree<T>::compare(const T& v1, const T& v2) const
    {
        if (v1 == v2) return 0;
        return v1 < v2 ? -1 : 1;
    }

    template<typename T>
    std::shared_ptr<TreeNode<T>> BSTree<T>::get_node(const T &value) const
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