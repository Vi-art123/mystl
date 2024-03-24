//
// Created by wyx on 2024/3/24.
// 基于链表的集合
//
#pragma once

#include "Set.hpp"
#include <LinkedList.hpp>

namespace mystd
{
    template<typename T>
    class ListSet : public Set<T>
    {
    public:
        [[nodiscard]] int size() const noexcept override { return list.size(); }
        [[nodiscard]] bool isEmpty() const noexcept override { return list.isEmpty(); }
        void clear() override { list.clear(); }
        bool contains(const T& value) const override { return list.contains(value); }

        void add(const T& value) override
        {
            int index = list.index_of(value);
            if (index != List<T>::ELEMENT_NOT_FOUND) {
                list.set(index, value);
            } else {
                list.push_back(value);
            }
        }

        void remove(const T& value) override
        {
            int index = list.index_of(value);
            if (index != List<T>::ELEMENT_NOT_FOUND) {
                list.remove(index);
            }
        }

        void traversal() override
        {
            list.to_string();
        }

    private:
        LinkedList<T> list;
    };
}