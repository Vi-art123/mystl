//
// Created by wyx on 2024/3/26.
// 优先级队列（按优先级高低出队）
//
#pragma once

#include <BinaryHeap.hpp>

namespace mystd
{
    template<typename T>
    class PriorityQueue
    {
    public:
        explicit PriorityQueue(const Heap<T>::Comp_func_t& compFunc = nullptr) : heap(std::move(BinaryHeap<T>(compFunc))) {}
        int size() { return heap.size(); }
        bool isEmpty() { return heap.isEmpty(); }
        void clear() { heap.clear(); }
        void enQueue(const T& value) { heap.add(value); }
        void deQueue() { heap.remove(); }
        T front() { return heap.get(); }
        void to_string() { heap.to_string(); }

    private:
        BinaryHeap<T> heap; // 使用二叉堆实现
    };
}