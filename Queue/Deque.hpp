//
// Created by wyx on 2024/3/17.
// 双端队列
//
#pragma once

#include <LinkedList.hpp>

namespace mystd
{
    template<typename T>
    class Deque
    {
    public:
        int size() { return list.size(); }
        bool isEmpty() { return list.isEmpty(); }
        void clear() { list.clear(); }
        void enQueueRear(const T& value) { list.push_back(value); }
        void deQueueRear() { list.pop_back(); }
        void enQueueFront(const T& value) { list.add(0, value); }
        void deQueueFront() { list.remove(0); }
        T front() { return list.get(0); }
        T rear() { return list.get(list.size() - 1); }
        void to_string() { list.to_string(); }

    private:
        LinkedList<T> list; // 优先使用双向链表，因为队列主要是头尾操作，双向链表效率更高
    };
}