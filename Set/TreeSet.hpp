//
// Created by wyx on 2024/3/24.
// 基于红黑树的集合
//
#pragma once

#include "Set.hpp"
#include <TreeMap.hpp>

namespace mystd
{
    template<typename T>
    class TreeSet : public Set<T>
    {
    public:
        [[nodiscard]] int size() const noexcept override { return tree_map.size(); }
        [[nodiscard]] bool isEmpty() const noexcept override { return tree_map.isEmpty(); }
        void clear() override { tree_map.clear(); }
        bool contains(const T& value) const override { return tree_map.containsKey(value); }
        void add(const T& value) override { tree_map.put(value, nullptr);}
        void remove(const T& value) override { tree_map.remove(value); }
        void traversal() override
        {
            tree_map.traversal();
        }

    private:
        TreeMap<T, void*> tree_map;
    };
}
