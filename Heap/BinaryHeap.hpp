//
// Created by wyx on 2024/3/25.
// 二叉堆（逻辑结构为完全二叉树，也叫完全二叉堆），使用数组（物理结构）实现
// 完全二叉树的规律可以用数组来实现
// 最大堆
//
#pragma once

#include "Heap.hpp"
#include <stdexcept>
#include <iostream>

namespace mystd
{
    template<typename T>
    class BinaryHeap : public Heap<T>
    {
    public:
        explicit BinaryHeap(const Heap<T>::Comp_func_t& compFun = nullptr) : BinaryHeap(nullptr, DEFAULT_CAPACITY, compFun) {}

        BinaryHeap(T arr[], int _size, const Heap<T>::Comp_func_t& compFun = nullptr)
        {
            this->setComparator(compFun);
            m_capacity = std::max(_size, DEFAULT_CAPACITY);
            m_arr = new T[m_capacity];
            if (arr != nullptr) {
                for (int i = 0; i < _size; i++) {
                    m_arr[i] = arr[i];
                }
                this->m_size = _size;
                heapify();
            }
        }

        ~BinaryHeap()
        {
            delete[] m_arr;
        }

        BinaryHeap(const BinaryHeap& _heap) : Heap<T>(_heap), m_capacity(_heap.m_capacity)
        {
            m_arr = new T[m_capacity];
            for (int i = 0; i < this->m_size; i++) {
                m_arr[i] = _heap.m_arr[i];
            }
        }

        BinaryHeap(BinaryHeap&& _heap) noexcept : Heap<T>(std::move(_heap)), m_capacity(_heap.m_capacity), m_arr(_heap.m_arr)
        {
            _heap.m_arr = nullptr;
            _heap.m_size = 0;
            _heap.m_capacity = DEFAULT_CAPACITY;
        }

        BinaryHeap& operator=(const BinaryHeap& _heap) noexcept
        {
            // 先拷贝一个临时对象，再交换到当前对象，避免自我赋值和异常
            BinaryHeap(_heap).swap(*this);
            return *this;
        }

        BinaryHeap& operator=(BinaryHeap&& _heap) noexcept
        {
            // 先移动到一个临时对象，再交换到当前对象
            BinaryHeap(std::move(_heap)).swap(*this);
            return *this;
        }

        void clear() noexcept override { this->m_size = 0; }
        void add(const T& value) override;   // 添加元素
        T get() const override;    // 获取堆顶元素
        T remove() override; // 删除堆顶元素
        T replace(const T& value) override;  // 删除堆顶元素的同时插入一个新元素

        void to_string() const;

    private:
        void swap(BinaryHeap& _heap) noexcept;
        void empty_check() const;
        void ensure_capacity();
        void trim_capacity();
        void sift_up(int index);    // 上滤
        void sift_down(int index);  // 下滤
        void heapify(); // 批量建堆
        [[nodiscard]] int free_space() const noexcept { return m_capacity - this->m_size; }

    private:
        static constexpr int DEFAULT_CAPACITY = 10;
        int m_capacity = DEFAULT_CAPACITY;
        T *m_arr = nullptr;
    };

    template<typename T>
    inline void BinaryHeap<T>::add(const T &value)
    {
        ensure_capacity();  // 扩容
        m_arr[this->m_size++] = value;
        sift_up(this->m_size - 1);
    }

    template<typename T>
    inline T BinaryHeap<T>::get() const
    {
        empty_check();
        return m_arr[0];
    }

    template<typename T>
    inline T BinaryHeap<T>::remove()
    {
        empty_check();
        int lastIndex = --this->m_size;
        auto root = m_arr[0];
        m_arr[0] = m_arr[lastIndex];
        sift_down(0);

        // 缩容
        trim_capacity();
        return root;
    }

    template<typename T>
    inline T BinaryHeap<T>::replace(const T &value)
    {
        auto root = T();
        if (this->m_size == 0) {
            m_arr[0] = value;
            this->m_size++;
        } else {
            root = m_arr[0];
            m_arr[0] = value;
            sift_down(0);
        }

        return root;
    }

    /**
     * 让index位置的元素上滤
     * @param index
     */
    template<typename T>
    void BinaryHeap<T>::sift_up(int index)
    {
        while (index > 0)
        {
            int parentIndex = (index - 1) >> 1;  // 父节点索引
            if (this->compare(m_arr[index], m_arr[parentIndex]) <= 0) return;

            // 交换index、parentIndex位置的内容
            std::swap(m_arr[index], m_arr[parentIndex]);

            // 重新赋值index
            index = parentIndex;
        }
    }

    /**
     * 让index位置的元素下滤
     * @param index
     */
    template<typename T>
    void BinaryHeap<T>::sift_down(int index)
    {
        int half = this->m_size >> 1;
        // 必须保证index位置是非叶子节点（index小于第一个叶子节点的索引）
        // 第一个叶子节点的索引等于非叶子节点的数量
        while (index < half)
        {
            // index位置的节点有2种情况（完全二叉树性质）
            // 1.只有左子节点
            // 2.同时有左右子节点

            // 默认为左子节点跟它进行比较
            int childIndex = (index << 1) + 1;

            // 右子节点
            int rightIndex = childIndex + 1;

            // 选出左右子节点最大的那个
            if (rightIndex < this->m_size && this->compare(m_arr[rightIndex], m_arr[childIndex]) > 0) {
                childIndex = rightIndex;
            }

            if (this->compare(m_arr[index], m_arr[childIndex]) >= 0) return;

            // 将子节点与index交换
            std::swap(m_arr[index], m_arr[childIndex]);

            index = childIndex;
        }
    }

    /**
     * 批量建堆
     */    
    template<typename T>
    void BinaryHeap<T>::heapify()
    {
#if 0
        // 自上而下的上滤（效率较低）
        for (int i = 1; i < this->m_size; i++) {
            sift_up(i);
        }
#endif
        // 自下而上的下滤（只上滤非叶子节点）
        for (int i = (this->m_size >> 1) - 1; i >= 0; i--) {
            sift_down(i);
        }
    }

    template<typename T>
    inline void BinaryHeap<T>::swap(BinaryHeap& _heap) noexcept
    {
        std::swap(m_arr, _heap.m_arr);
        std::swap(this->m_size, _heap.m_size);
        std::swap(m_capacity, _heap.m_capacity);
    }

    template<typename T>
    void BinaryHeap<T>::empty_check() const
    {
        if (this->m_size == 0) {
            throw std::out_of_range("Heap is empty.");
        }
    }

    /**
     * 动态扩容
     */
    template<typename T>
    inline void BinaryHeap<T>::ensure_capacity()
    {
        if (free_space() > 0) return;
        m_capacity += (m_capacity >> 1);
        T* new_arr = new T[m_capacity];
        for (int i = 0; i < this->m_size; i++) {
            new_arr[i] = m_arr[i];
        }
        delete[] m_arr;
        m_arr = new_arr;
    }

    /**
     * 动态缩容
     */
    template<typename T>
    void BinaryHeap<T>::trim_capacity()
    {
        if (this->m_size >= (m_capacity >> 1)
            || m_capacity <= DEFAULT_CAPACITY)
            return;

        m_capacity >>= 1;
        T* new_arr = new T[m_capacity];
        for (int i = 0; i < this->m_size; i++) {
            new_arr[i] = m_arr[i];
        }
        delete[] m_arr;
        m_arr = new_arr;
    }

    template<typename T>
    void BinaryHeap<T>::to_string() const
    {
        std::cout << "size:" << this->m_size << ", ";
        std::cout << "{";
        for (int i = 0; i < this->m_size; i++) {
            std::cout << m_arr[i];
            if (i != this->m_size - 1) std::cout << ", ";
        }
        std::cout << "}" << std::endl;
    }
}