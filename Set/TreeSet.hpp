//
// Created by wyx on 2024/3/24.
// 基于红黑树的集合
//
#pragma once

#include "Set.hpp"
#include <RBTree.hpp>

namespace mystd
{
    template<typename T>
    class TreeSet : public Set<T>
    {
    public:
        [[nodiscard]] int size() const noexcept override { return rbTree.size(); }
        [[nodiscard]] bool isEmpty() const noexcept override { return rbTree.isEmpty(); }
        void clear() override { rbTree.clear(); }
        bool contains(const T& value) const override { return rbTree.contains(value); }
        void add(const T& value) override { rbTree.add(value);}
        void remove(const T& value) override { rbTree.remove(value); }
        void traversal() override
        {
            std::cout << "size:" << size() << ", ";
            std::cout << "[ ";
            rbTree.inOrderTraverse();
            std::cout << "]";
            std::cout << std::endl;
        }

    private:
        RBTree<T> rbTree;
    };
}
