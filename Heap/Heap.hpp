//
// Created by wyx on 2024/3/25.
// 堆 基类
//
#pragma once

#include <functional>

namespace mystd
{
    template<typename T>
    class Heap
    {
    public:
        using Comp_func_t = std::function<int(const T&, const T&)>;

        Heap() = default;
        Heap(const Heap&) = default;
        Heap(Heap&&) = default;
        virtual ~Heap() = default;

        [[nodiscard]] int size() const { return m_size; }
        [[nodiscard]] bool isEmpty() const { return m_size == 0; }
        virtual void clear() = 0;
        virtual void add(const T& value) = 0;   // 添加元素
        virtual T get() const = 0;    // 获取堆顶元素
        virtual T remove() = 0; // 删除堆顶元素
        virtual T replace(const T& value) = 0;  // 删除堆顶元素的同时插入一个新元素

        void setComparator(const Comp_func_t& _func) { Comp = std::move(_func); }
    protected:
        int compare(const T& v1, const T& v2) const noexcept
        {
            if (Comp == nullptr) {
                if (v1 == v2) return 0;
                return v1 < v2 ? -1 : 1;
            }

            return Comp(v1, v2);
        }
    protected:
        int m_size = 0;

    private:
        Comp_func_t Comp;
    };
}