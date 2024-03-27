//
// Created by wyx on 2024/3/27.
// 排序算法基类
//
#pragma once

#include <string.h>
#include <utility>
#include <TimeCount.h>

namespace mystd
{
    class Sort
    {
    public:
        Sort(int *arr, int size, std::string s_name = "") : m_size(size), sort_name(s_name)
        {
            m_arr = new int[m_size];
            memcpy(m_arr, arr, sizeof(int) * m_size);
        }
        Sort(const Sort&) = delete;
        Sort(Sort&&) = delete;
        virtual ~Sort()
        {
            delete[] m_arr;
        }

        Sort& operator=(const Sort&) = delete;

        virtual void sort() = 0;

        [[nodiscard]] int getCountCompare() const noexcept { return countCompare; }
        [[nodiscard]] int getSwapCount() const noexcept { return swapCount; }

        void to_string() const
        {
            std::cout << "【" + sort_name + "】" << std::endl;
            std::cout << "size=" << m_size << ", ";
            std::cout << "{";
            for (int i = 0; i < m_size; i++) {
                if (i != 0)
                    std::cout << ", ";
                std::cout << m_arr[i];
            }
            std::cout << "}";
            std::cout << std::endl;
            std::cout << "compare:" << getCountCompare() << ", swap:" << getSwapCount() << std::endl;
            std::cout << "耗时：" << std::fixed << timeCount/1000000.0 << " s" << std::endl;
        }

    protected:
        int compare(int v1, int v2) noexcept
        {
            countCompare++;
            return v1 - v2;
        }

        void swap(int& v1, int& v2) noexcept
        {
            swapCount++;
            std::swap(v1, v2);
        }

    protected:
        int m_size = 0;
        int64_t timeCount = 0;
        int *m_arr = nullptr;
    private:
        int countCompare = 0;
        int swapCount = 0;
        std::string sort_name;
    };
}