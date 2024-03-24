//
// Created by wyx on 2024/3/24.
// 基于红黑树实现的map
//
#pragma once

#include "Map.hpp"
#include <memory>

namespace mystd
{
    template<typename K, typename V>
    struct TMNode
    {
        K key;
        V value;

        std::weak_ptr<TMNode> parent;
        std::shared_ptr<TMNode> left;
        std::shared_ptr<TMNode> right;
        TMNode() = default;
        TMNode(const TMNode& node) = default;
        TMNode(TMNode&& node) = default;
        TMNode(const K& k, const V& val, std::weak_ptr<TMNode> p) : key(k), value(val), parent(p) {}
//        virtual ~TMNode() { std::cout << "delete TMNode: " << key << ":" << value << std::endl; }

        /**
         * 节点转换为字符串
         * @return 
         */
        [[nodiscard]] virtual std::string toString() const
        {
            std::string str = std::to_string(value);
            str.append("_p(");
            if (auto p = parent.lock()) {
                str.append(std::to_string(p->value));
            } else {
                str.append("null");
            }
            str.push_back(')');

            return str;
        }

        /**
         * 度是否为2
         * @return 
         */
        [[nodiscard]] bool hasTwoChildren() const noexcept
        {
            return (left != nullptr && right != nullptr);
        }

        /**
         * 是否为叶子节点
         * @return 
         */
        [[nodiscard]] bool isLeaf() const noexcept
        {
            return (left == nullptr && right == nullptr);
        }

        /**
         * 判断节点是否在左边
         * @return 
         */
        [[nodiscard]] bool isLeftChild() const noexcept
        {
            return (parent.lock() && this == parent.lock()->left.get());
        }

        /**
         * 判断节点是否在右边
         * @return 
         */
        [[nodiscard]] bool isRightChild() const noexcept
        {
            return (parent.lock() && this == parent.lock()->right.get());
        }

        /**
         * 获取兄弟节点
         * @return
         */
        std::shared_ptr<TMNode> sibling() const noexcept
        {
            if (!parent.lock()) {
                return nullptr;
            }
            return isLeftChild() ? parent.lock()->right : parent.lock()->left;
        }
    };
    
    template<typename K, typename V>
    class TreeMap : public Map<K, V>
    {
    public:
        [[nodiscard]] int size() const noexcept override;
        [[nodiscard]] bool isEmpty() const noexcept override;
        void clear() override;

        V put(const K& key, const V& value) override;

        V get(const K& key) const override;
        void remove(const K& key) override;
        bool containsKey(const K& key) const override;
        bool containsValue(const V& value) const override;
        void traversal() override;
    };
}